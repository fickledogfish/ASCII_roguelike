#pragma once

struct Coordinates {
    int row;
    int col;

    Coordinates(int x, int y) : row(x), col(y) {};
    Coordinates(const Coordinates& c) : row(c.row), col(c.col) {};
    bool operator==(const Coordinates& other);
};

enum struct Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
Validates a movement character. Use this immediately before calling `Direction
translateMovementChar(char c)`, as this is made to prevent this function from
throwing an error.
*/
bool isValidMovementChar(char c);

/**
Translates a moviment character into a `direction`.

Throws `std::logic_error` if an invalid character is passed.
*/
Direction translateMovementChar(char c);
