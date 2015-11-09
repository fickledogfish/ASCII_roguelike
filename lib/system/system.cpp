#include "system.hpp"

#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <sstream>
#include <iomanip>
#include "text.hpp"
#include "../../src/Map.hpp"

namespace fs = boost::filesystem;

void sys::pause() {
    std::cout << "Press ENTER to continue...";
    std::cin.ignore();
}

bool sys::fileHasExtension(std::string filename, std::string extension) {
    // automagically add a dot to the extension, in case of need
    extension = (extension.empty() || extension.at(0) == '.')? extension : "." + extension;

    return filename.size() >= extension.size() &&
           filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

std::vector<std::string> sys::lstfiles(std::string folderpath, std::string extension, bool sort) {
    std::vector<std::string> contents;

    if (fs::exists(folderpath)) {
        for(fs::directory_iterator it(folderpath); it != fs::directory_iterator(); ++it) {
            if(!is_directory(it->status()) && sys::fileHasExtension(it->path().filename().c_str(), extension))
                contents.push_back(it->path().filename().c_str());
        }
    }

    if (sort)
        std::sort(contents.begin(), contents.end());

    return contents;
}

void sys::clearScreen() {
    std::cout << std::string(100,'\n');
}


void sys::printSystemInfo() {
    std::stringstream s;
    s << config::PROJECT_NAME << " v" << config::VERSION_MAJOR << "." << config::VERSION_MINOR
      << (config::DEBUG_MODE? "[debug]\nWARNING: DEBUG MODE ON" : "") << std::endl;

    txt::printCentered(s.str(), 80);

    if(config::DEBUG_MODE) {
        std::cout << "Boost version " << std::setfill('0')
                  << std::setw(1) << BOOST_VERSION / 100000     << "."
                  << std::setw(3) << BOOST_VERSION / 100 % 1000 << "."
                  << std::setw(2) << BOOST_VERSION % 100
                  << std::endl;
    }

}

bool sys::checkSanity(std::string mapfile, std::map<char,char> mapchars, std::string prefix) {
    bool is_valid = true;

    std::string filepath = prefix + mapfile;

    try {
        Map testmap(filepath, mapchars, true);
        if(config::DEBUG_MODE)
            std::cout << "Sanity of " << mapfile << "..." << " ok." << std::endl;
    } catch (const std::invalid_argument &e) {
        is_valid = false;
        if(config::DEBUG_MODE)
            std::cout << "Sanity of " << mapfile << "..." << " invalid." << std::endl;
    }

    return is_valid;
}

bool sys::checkSanityAll(std::string path, std::map<char,char> mapchars) {
    bool all_valid = true;

    for (std::string file : sys::lstfiles(path, "level")) {
        if (!sys::checkSanity(file, mapchars, path)) {
            all_valid = false;
            break;
        }
    }

    if (!all_valid && config::DEBUG_MODE) {
        std::cout << "Found invalid file(s). Please correct them." << std::endl;
    }

    return all_valid;
}
