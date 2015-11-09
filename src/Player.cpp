#include "Player.hpp"

#include <iostream>
#include <limits>
#include <string>
#include "Map.hpp"
#include "system.hpp"

bool Player::move(Map& current_map) {
    std::string input;
    Direction d;

    /*
    Loop untill the user enters a valid character.

        1. ensure the user only entered one character;
        2. test this character for validation;
        3. transform the character into the direction of the movement;
        4. actually move the player.
    */
    std::cout << "Enter your move (w/s/a/d): ";
    std::getline(std::cin, input);

    while(std::cin.fail() || input.length() != 1 || !isValidMovementChar(input[0])) {
        std::cin.clear();

        std::cout << "Please enter a valid movement character: ";
        std::getline(std::cin, input);
    }

    d = translateMovementChar(input[0]);

    if(Player::validateMove(current_map, Player::virtualMovement(d))) {
        Player::moveToDirection(d);
        return true;
    } else {
        return false;
    }
}

void Player::fight(Enemy& e) {
    while(true) {
        Player::attack(e);
        if (e.isDead()) break; // does not make sense to let the enemy attack if it is already dead, right?

        e.attack(*this);
        if (Player::isDead()) break;
    }

    sys::pause();
}
