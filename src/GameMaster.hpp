#pragma once

#include <map>
#include <vector>
#include <list>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Map.hpp"
#include "system.hpp"

/**
Master of the game, it controlls all life within this universe.
*/
class GameMaster {

private:
    static int _num_masters; // thou shalt not have two or more masters
    std::map<char,char> _mapchars; // maps the representation in a `.level` file to the output for the user
    std::vector<std::string> _valid_maps; // playable maps
    std::list<Enemy> _enemies; // all living enemies in the current map

public:
    /**
    Minimum constructor for the GameMaster.

    @param mapchars maps the representation in a `.level` file to the output for the user
    */
    GameMaster(std::map<char,char> mapchars);

    //selectMap();
    //playMap();

    /**
    Checks the sanity of all found maps.
    */
    bool checkSanityAll();

    /**
    Creates a player and play untill it dies or the map ends.
    */
    void playGame(bool sanity_check = true);

private:
    /**
    Removes dead enemies from the list.
    */
    void _cleanEnemies();

    /**
    Moves the player on the map.
    */
    void _movePlayer(Player& p, Map& current_map);

    /**
    Moves all living enemies on the map. Remember to call _cleanEnemies() before
    this.
    */
    void _moveEnemies(Map& current_map);

    /**
    Fight enemies, if possible.
    */
    void _checkForFights(Player& p);
};
