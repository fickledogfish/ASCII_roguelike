/*

=== Data Definitions ===

RawMap: String
    Defines the map as read from the file.

Map: VectorOf(VectorOf(Char))
    Defines the loaded map.

MapChars: std::Map(Char, Char)
    Defines the translation between the representation and the printed version
    of the Map.
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include "Coordinates.hpp"

class Map {
private:
    std::string _mapstr;                  // Data::RawMap
    std::vector<std::vector<char>> _map;  // Data::Map
    const std::map<char,char> _mapchars;  // Data::MapChars
    bool _sanity_only;                    // was this build only for sanity tests?
    std::map<std::string, char> _overlap;

public:
    Map(std::string filepath, std::map<char,char> mapchars, bool sanity_only = false);

    /**
    Translates a character into its representation on the map, using the current
    `mapchar` map.
    */
    char translateChar(int row, int col);

    /**
    Prints the map to the screen.
    */
    void printMap();

    /**
    Add a position to be overlapped.
    */
    void overlap(int row, int col, char new_val);

    /**
    Overlap using a coordinate structure.
    */
    void overlap(Coordinates point, char new_val);

    /**
    Removes all overlapped data.
    */
    void clearOverlap();

    // === Getters ===

    /**
    Gets the representation of what is in the desired block.
    */
    char getBlock(int row, int col) { return _map[row][col]; };

    char getBlock(const Coordinates c) { return Map::getBlock(c.row, c.col); };

private:

    /**
    Checks if the object was build for sanity-checks only.

    Throws an exception if the object is build for sanity only;
    */
    void _isSanityObject();

    /**
    Open and load the map in filepath, checking its sanity first. This does not
    translate the map into _map, but only reads the string from the file.
    */
    bool _loadMapStr(std::string filepath);

    /**
    Checks consistency of line and column size in the desired file.
    */
    bool _checkLinesAndCols();

    /**
    Checks the sanity of a map.

    This is made to ensure that, not only the number of lines ans columns are
    correct, but also the characters used must be in the list of permitted
    values.
    */
    bool _sanityCheck();

    /**
    Tests the translation map against the vector of allowed chars.
    */
    bool _checkMapChars();

    /**

    */
    void _buildMap();

    /**
    Checks if the current point should be overlapped.
    */
    bool _overlapPoint(int row, int col);

    /**
    Get the value the point should be overlapped with.
    */
    char _getOverlappedPoint(int row, int col);
};
