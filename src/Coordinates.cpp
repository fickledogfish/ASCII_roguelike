#include "Coordinates.hpp"

#include <stdexcept>

bool Coordinates::operator==(const Coordinates& other) {
    return Coordinates::row == other.row &&
           Coordinates::col == other.col;
}

bool isValidMovementChar(char c) {
    bool is_valid;

    switch(c) {
    case 'w':
    case 's':
    case 'a':
    case 'd':
        is_valid = true;
        break;
    default:
        is_valid = false;
        break;
    }

    return is_valid;
}

Direction translateMovementChar(char c) {
    Direction d;

    switch(c) {
    case 'w':
        d = Direction::UP;
        break;
    case 's':
        d = Direction::DOWN;
        break;
    case 'a':
        d = Direction::LEFT;
        break;
    case 'd':
        d = Direction::RIGHT;
        break;
    default:
        throw std::logic_error("Invalid character for moviment found.");
        break;
    }

    return d;
}
