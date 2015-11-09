#include "Map.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>
#include "config.hpp"
#include "MapComponents.hpp"

Map::Map(std::string filepath, std::map<char,char> mapchars, bool sanity_only)
    : _mapchars{mapchars}, _sanity_only{sanity_only} {

    if (!Map::_loadMapStr(filepath)) {
        throw std::invalid_argument("Invelid map passed.");
    }

    if(!Map::_sanity_only) {
        Map::_buildMap();  // transform the string into a vector of vectors
        Map::_mapstr = ""; // the string is not needed anymore
    }
}

void Map::_isSanityObject() {
    if (Map::_sanity_only)
        throw std::logic_error("Object was build for sanity check only.");
}

bool Map::_loadMapStr(std::string filepath) {
    std::ifstream mapfile(filepath);

    if (mapfile.is_open()) {
        std::stringstream mapstream;
        std::string line;

        while(std::getline(mapfile, line)) {
            mapstream << line << std::endl;
        }

        mapfile.close();

        Map::_mapstr = mapstream.str();
    } else {
        // unable to open file
        return false;
    }

    // map was opened and loaded successfully, but now we have to validade it
    return Map::_sanityCheck();
}

bool Map::_sanityCheck() {
    for(char c : Map::_mapstr) {
        auto search = _mapchars.find(c);
        if (c != '\n' && search == _mapchars.end()) {
            return false;
        }
    }

    return Map::_checkMapChars() && Map::_checkLinesAndCols();
}

bool Map::_checkMapChars() {
    // checks to see if every allowed char is present
    for(int i = 0; i < ALLOWED_CHARS.size(); i++) {
        auto search = Map::_mapchars.find(ALLOWED_CHARS[i]);
        if (search == Map::_mapchars.end())
            return false;
    }

    // and to see if the map only contains allowed chars
    for(std::map<char,char>::const_iterator it = Map::_mapchars.begin(); it != Map::_mapchars.end(); ++it) {
        bool found = false;
        for(auto c : ALLOWED_CHARS) {
            if (it->first == c)
                found = true;
        }
        if (!found)
            return false;
    }

    return true;
}

bool Map::_checkLinesAndCols() {
    int number_of_cols = 0;
    std::vector<int> chars_per_line;

    /*
    Validating the file char by char.

    To validate the file, we need to check the number of characters in each
    line and the total number of lines in the file.
    */
    for (char &ch : Map::_mapstr) {
        /*
        if the number of lines is already greater than the allowed size,
        there is no need to continue checking
        */
        if (chars_per_line.size() > config::MAP_SIZE.rows)
            return false;

        if (ch == '\n') {
            chars_per_line.push_back(number_of_cols);
            number_of_cols = 0;
        } else {
            number_of_cols++;
        }
    }

    /*
    Time to check the columns.

    Before complete validation, we need to know if every column has the same
    number of characters in it.
    */
    for(int i = 0; i < chars_per_line.size() - 1; i++)
        if (chars_per_line[i] != chars_per_line[i+1])
            return false;

    /*
    The only thing left to validate the lines is to check the column and line
    size.

    For that, we already know that every line has the same number of characers.
    So, if the first is not valid, any other will be. The number of lines is
    just a size check.
    */
    return (chars_per_line[0] == config::MAP_SIZE.cols) && (chars_per_line.size() == config::MAP_SIZE.rows);
}

void Map::_buildMap() {
    // resize the map vector to ensure thigs will fit
    Map::_map.resize(config::MAP_SIZE.rows);
    for (auto &row : Map::_map)
        row.resize(config::MAP_SIZE.cols);

    int count_rows = 0;
    int count_cols = 0;

    for(char &ch : Map::_mapstr) {
        if (ch == '\n') {
            count_rows++;
            count_cols = 0;
        } else {
            Map::_map[count_rows][count_cols] = ch;
            count_cols++;
        }
    }
}

char Map::translateChar(int row, int col) {
    return Map::_mapchars.at(Map::_map[row][col]);
}

void Map::printMap() {
    Map::_isSanityObject();
    // substitute every char in the map file for the desired printable ones
    for (std::vector<std::vector<char>>::size_type row = 0; row < Map::_map.size(); row++) {
        for (std::vector<std::vector<char>>::size_type col = 0; col < Map::_map[0].size(); col++)
            // if an overlap is defined, print it instead of the intended char
            std::cout << (Map::_overlapPoint(row, col) ? Map::_getOverlappedPoint(row, col)
                                                       : Map::translateChar(row, col));
        std::cout << std::endl;
    }
}

void Map::overlap(int row, int col, char new_val) {
    std::stringstream s;
    s << row << "x" << col;
    Map::_overlap[s.str()] = new_val;
}

void Map::overlap(Coordinates point, char new_val) {
    Map::overlap(point.row, point.col, new_val);
}

void Map::clearOverlap() {
    Map::_overlap.clear();
}

bool Map::_overlapPoint(int row, int col) {
    std::stringstream s;
    s << row << "x" << col;
    return Map::_overlap.find(s.str()) != Map::_overlap.end();
}

char Map::_getOverlappedPoint(int row, int col) {
    std::stringstream s;
    s << row << "x" << col;
    return Map::_overlap.find(s.str())->second;
}
