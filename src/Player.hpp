#pragma once

#include "Entity.hpp"
#include "Coordinates.hpp"
#include "Map.hpp"
#include "Enemy.hpp"

class Player : public Entity {

public:
    Player(int start_x, int start_y, std::string name, char representation, unsigned int max_health, unsigned int attack)
        : Entity(start_x, start_y, name, representation, max_health, attack) {};

    /**
    Needed because of `Entity`'s `virtual void move()`.

    In this case, ask for a character input from the user, validate it,
    transform it into a Direction and only then change the `Player`'s current
    position.

    Validation is made with `bool isValidMovementChar(char c)` and translation
    is made with `Direction translateMovementChar(char c)`, both from
    `Coordinates.hpp`.
    */
    bool move(Map& current_map);

    /**
    Fights the `Enemy` till death.
    */
    void fight(Enemy& e);

};
