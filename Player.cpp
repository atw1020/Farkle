//
// Created by arthur wesley on 9/21/20.
//

#include "Player.h"
#include "IO.h"

/**
 *
 * constructor
 *
 * @param name name of the player
 */
Player::Player(std::string name) {
    this->name = name;
    score = 0;
}

/**
 *
 * score a number of points for the player
 *
 * @param points number of points to score
 */
void Player::scorePoints(int points) {
    if (isInGame() or points >= 500){
        score += points;
    }
    else{
        printNotInGame(this, points);
    }
}

/**
 *
 * get the player's score
 *
 * @return the score of the player
 */
int Player::getScore() {
    return score;
}

/**
 *
 * getter method for the name
 *
 * @return the name of the player
 */
std::string Player::getName(){
    return name;
}

/**
 *
 * select which dice to keep
 *
 * @param dice the dice to choose from
 * @return vector of the dice that we desire to be scored
 * @return empty vector if there was an error
 */
std::vector<int> Player::chooseDice(std::vector<int> *dice, int storedScore) {

    printRollStatus(dice, storedScore);

    return parse_input(dice);
}

std::string Player::status() {
    return name + " has " + std::to_string(score) + " points";
}

bool Player::isSilent() {
    return silent;
}

bool Player::isInGame() {
    return score >= 500;
}


