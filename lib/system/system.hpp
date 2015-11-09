/**
This file lists functions related to system and file manipulation that are out
of the scope for other files.
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include "config.hpp"

namespace sys {

    /**
    Pauses execution and wait for the player to press enter.
    */
    void pause();

    /**
    Checks to see if a given `filename` ends with an `extension`.

    Note that `extension` may leave the dot behind, as it will be added by the
    function automagically.
    */
    bool fileHasExtension(std::string filename, std::string extension);

    /**
    List all files in `folderpath` that have the extension. The returned vector
    is sorted.

    The extension may exclude the dot. See `fileHasExtension`.

    To list all files, simply leave extension as an empty string.
    */
    std::vector<std::string> lstfiles(std::string folderpath, std::string extension = "", bool sort = true);

    /**
    Clears the current text in screen the most stupid way possible: printing one
    hundred new lines of nothing.

    Good thing is, this is OS-independent.
    */
    void clearScreen();

    /**
    Prints initial information on the screen.

    If the program was build using the debug flag, also prints aditional
    information that may be important.
    */
    void printSystemInfo();

    /**
    Checks the sanity of a map.
    */
    bool checkSanity(std::string mapfile, std::map<char,char> mapchars, std::string prefix = "resources/levels/");

    /**
    Checks the sanity of all maps in `path`.
    */
    bool checkSanityAll(std::string path, std::map<char,char> mapchars);
}
