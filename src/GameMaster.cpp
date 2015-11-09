#include "GameMaster.hpp"

#include <iostream>
#include <stdexcept>
#include "system.hpp"
#include "config.hpp"

int GameMaster::_num_masters = 0;

GameMaster::GameMaster(std::map<char,char> mapchars) : _mapchars(mapchars) {
    ++_num_masters;

    if (_num_masters > 1)
        throw std::logic_error("There must be only one GameMaster.");

    // loads all valid maps
}

bool GameMaster::checkSanityAll() {
    return sys::checkSanityAll(config::LEVELS_FOLDER, GameMaster::_mapchars);
}

void GameMaster::_cleanEnemies() {
    _enemies.remove_if( [](Enemy& e) -> bool { return e.isDead(); } );
}

void GameMaster::_movePlayer(Player& p, Map& current_map) {
    while(!p.move(current_map)) {
        std::cout << "You cannot move to that block!" << std::endl;
    }
}

void GameMaster::_moveEnemies(Map& current_map) {
    for (Enemy &e : _enemies)
        while(!e.move(current_map))
            ; // do nothing, e.move already does the job
}

void GameMaster::_checkForFights(Player& p) {
    for (Enemy& e : _enemies) {
        if (p.getPosition() == e.getPosition()) {
            p.fight(e);
        }
    }

    GameMaster::_cleanEnemies();
}

void GameMaster::playGame(bool sanity_check) {
    sys::printSystemInfo();

    bool found_invalid = false;

    if (sanity_check)
        found_invalid = GameMaster::checkSanityAll();

    Map first_level(config::LEVELS_FOLDER + "01.level", GameMaster::_mapchars);
    Player p(0, 10, "Player", '@', 5000, 20);

    // allocate a list of enemies in the heap
    _enemies.push_back(Enemy(1, 1, "Snake", 'S', 90, 10));
    _enemies.push_back(Enemy(10, 5, "Snake", 'S', 90, 10));
    _enemies.push_back(Enemy(12, 10, "Snake", 'S', 90, 10));

    // game loop
    while(!p.isDead()) {
        sys::clearScreen();

        first_level.clearOverlap();
        p.addToMap(first_level);

        for (Enemy &e : _enemies)
            e.addToMap(first_level);

        std::cout << "enemies left: " << _enemies.size() << std::endl
                  << "\tplayer position: " << p.getPosition().row << '\t' << p.getPosition().col << std::endl;

        int i = 0;
        for (std::list<Enemy>::iterator e_itr = _enemies.begin(); e_itr != _enemies.end(); ++e_itr) {
            Coordinates c = e_itr->getPosition();
            std::cout << "enemy " << i << " position: " << c.row << '\t' << c.col << '\t' << (c == p.getPosition()) << std::endl;
            i++;
        }

        first_level.printMap();

        p.printStatus();

        _movePlayer(p, first_level);
        _checkForFights(p);
        _moveEnemies(first_level);
        _checkForFights(p);

    }

}
