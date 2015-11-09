#include "Entity.hpp"

#include <iostream>
#include <cmath>
#include "MapComponents.hpp"
#include "config.hpp"

void Entity::moveToPoint(int row, int col) {
    Entity::_current_position.row = row;
    Entity::_current_position.col = col;
}

void Entity::relativeMove(int x, int y) {
    Entity::_current_position.row += y;
    Entity::_current_position.col += x;
}

void Entity::moveToDirection(Direction d) {
    switch(d) {
    case Direction::UP:
        Entity::relativeMove(0,-1);
        break;
    case Direction::DOWN:
        Entity::relativeMove(0,1);
        break;
    case Direction::LEFT:
        Entity::relativeMove(-1,0);
        break;
    case Direction::RIGHT:
        Entity::relativeMove(1,0);
        break;
    default:
        throw std::logic_error("Invalid direction passed to moveToDirection.");
        break;
    }
}

void Entity::takeDamage(unsigned int amount_of_damage) {
    Entity::_current_health -= amount_of_damage;
}

void Entity::attack(Entity& e) {
    e.takeDamage(Entity::_attack);
    std::cout << Entity::getName() << " attacks " << e.getName() << "!" << std::endl
              << '\t' << e.getName() << "'s health: " << e.getCurrentHealth()
              << '\t' << Entity::getName() << "'s health: " << Entity::getCurrentHealth() << std::endl;
}

/**
Create a bar string to represent a percentage of something.
*/
std::string _createBar(float current, float total, int size, char prefix = '[', char suffix = ']') {
    float fill_percent = (current)/total;
    int fill = std::round(fill_percent*size);
    int complement = size - fill;

    return prefix + std::string(fill, '=') + std::string(complement, ' ') + suffix;
}

void Entity::printStatus() {
    std::cout << "\tHealth: " << _createBar(_current_health, _max_health, config::BAR_SIZE)
              << " (" << Entity::_current_health << "/" << Entity::_max_health << ")" << std::endl
              << "\tAttack: " << Entity::getAttack() << std::endl;
}

bool Entity::validateMove(Map& current_map, Coordinates future_pos) {
    if ( future_pos.row < 0 || future_pos.row >= config::MAP_SIZE.rows ||
         future_pos.col < 0 || future_pos.col >= config::MAP_SIZE.cols )
        return false;

    char map_block = current_map.getBlock(future_pos);

    if (map_block == Components.WALL || map_block == Components.TREE)
        return false;

    return true;
}

bool Entity::cannotMove(Map& current_map) {
    std::vector<Direction> surrounding_blocks = { Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT };

    for (auto d : surrounding_blocks) {
        Coordinates future_pos = Entity::virtualMovement(d);

        if (validateMove(current_map, future_pos))
            return false;
    }

    return true;
}

Coordinates Entity::virtualMovement(const Direction d) {
    Coordinates future_position = Entity::_current_position;

    switch(d) {
    case Direction::UP:
        future_position.row--;
        break;
    case Direction::DOWN:
        future_position.row++;
        break;
    case Direction::LEFT:
        future_position.col--;
        break;
    case Direction::RIGHT:
        future_position.col++;
        break;
    default:
        throw std::logic_error("Invalid direction passed to virtualMovement.");
        break;
    }

    return future_position;
}

void Entity::addToMap(Map& current_map) {
    current_map.overlap(Entity::getPosition(), Entity::getRepresentation());
}
