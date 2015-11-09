/*

int main() {

    sys::checkSanity();

    Game game = ...;

    game.selectLevel();
    game.playGame();

    return 0;
}

*/

#include <iostream>
#include <vector>
#include <map>
#include "config.hpp"
#include "GameMaster.hpp"
#include "MapComponents.hpp"
#include "Coordinates.hpp"

int main() {

    std::map<char,char> mapchars = {
                                     { Components.WALL,   '#' },
                                     { Components.GROUND, '.' },
                                     { Components.GRASS,  ';' },
                                     { Components.TREE,   'T' }
                                   };

    GameMaster game(mapchars);

    //game.checkSanity();
    game.playGame(config::SANITY_CHECK_ALL);

    //sys::pause();

    //sys::clearScreen();
}
