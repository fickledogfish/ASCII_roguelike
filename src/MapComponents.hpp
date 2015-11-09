#pragma once

#include <string>
#include <vector>

/**
A generic component of the map.
*/
struct Component {
    bool walkable;   ///< if true, any Entity can walk over it
    char level_char; ///< representation in the `.level` files
    char print_char; ///< representation for the user

    /**
    Default constructor for the class.
    */
    Component(bool walkable, char level_char, char print_char);
};

struct TranslationList {
    char WALL;
    char GROUND;
    char GRASS;
    char TREE;
};

const TranslationList Components = {.WALL = 'w', .GROUND = 'g', .GRASS = ';', .TREE = 't'};

const std::vector<char> ALLOWED_CHARS = { Components.WALL,
                                          Components.GROUND,
                                          Components.GRASS,
                                          Components.TREE };
