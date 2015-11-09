#pragma once

#include "Entity.hpp"

#include "Map.hpp"
#include "random.hpp"

class Enemy : public Entity {

public:
    Enemy(int start_x, int start_y, std::string name, char representation, unsigned int max_health, unsigned int attack)
    : Entity(start_x, start_y, name, representation, max_health, attack) {};

    /**
    Needed because of `Entity`'s `virtual void move()`.

    Randomly moves the `Enemy` on the map.

    This will return true if the movement is possible or if the enemy is stuck
    between walls.
    */
    bool move(Map &current_map);
};
