/**
An Entity is anything that cam move across the map, take damage, attack and
heal.

Note this is only an interface, and cannot be instantiated, unless from a child
class.

All children are required to implement these functions:

    * bool move(const Map& current_map);

*/

#pragma once

#include <string>
#include "Coordinates.hpp"
#include "Map.hpp"

class Entity {

private:
    Coordinates _start_position;
    Coordinates _current_position;
    std::string _name;
    char _representation;
    int _max_health;
    int _current_health;
    unsigned int _attack;

protected:
    Entity(int start_x, int start_y, std::string name, char representation, int max_health = 100, unsigned int attack = 10)
        : _start_position(start_x, start_y), _current_position(_start_position),
          _name(name), _representation(representation), _max_health(max_health),
          _current_health(max_health), _attack(attack)
          {};

public:
    /**
    Checks if the entity died.
    */
    bool isDead() { return _current_health <= 0; };

    /**
    Actual movement function implementation depends on the type of Entity, so
    make sure to force each one to have its own.

    Also, make sure the move is valid in the current map.
    */
    virtual bool move(Map& current_map) = 0;

    /**
    Reduces current health based on amount of damage taken.
    */
    void takeDamage(unsigned int amount_of_damage);

    /**
    Attacks the entity `e`.

    `e` needs to be a reference or a pointer, since it will be modified.
    */
    void attack(Entity& e);

    /**
    Display current health, attack and other info, if it is added next.
    */
    void printStatus();

    /**
    Validates the move represented by the future position of the entity into the
    current map.
    */
    bool validateMove(Map& current_map, Coordinates future_pos);

    /**
    Checks if a move is possible.
    */
    bool cannotMove(Map& current_map);

    /**
    Change `position` to reflect a possible move in the direction `d`.
    */
    Coordinates virtualMovement(Direction d);

    /**
    Adds the current entity to the map.
    */
    void addToMap(Map& current_map);

    // === Getters ===

    std::string getName() { return Entity::_name; };

    Coordinates getPosition() { return Entity::_current_position; };

    int getCurrentHealth() { return Entity::_current_health; };

    char getRepresentation() { return Entity::_representation; };

    int getAttack() { return Entity::_attack; };

protected:
    /**
    Moves to a specific point on the map.
    */
    void moveToPoint(int row, int col);

    /**
    Moves `x` tiles right and `y` tiles down.

    Notice the coordinate system is SFML-like:

        .--------->
        |         x
        |
        |
        |
        V y
    */
    void relativeMove(int x, int y);

    /**
    Adds one tile to the desired direction.
    */
    void moveToDirection(Direction d);

};
