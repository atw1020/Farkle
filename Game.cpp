//
// Created by arthur wesley on 9/21/20.
//

#include <iostream>
#include "Game.h"
#include "IO.h"
#include "scorer.h"

#define GAME_END 10000

//
// constructors / destructors
//

/**
 *
 * constructor
 *
 * @param names names of players
 */
Game::Game(std::vector<std::string> names) {

    for (auto name : names){
        players.push_back(new Player(name));
    }

}

/**
 *
 * a constructor that takes in raw players
 *
 * @param players names of the players
 */
Game::Game(std::vector<Player*> players) {
    this->players = players;
    silent = false;
}

/**
 *
 * a constructor that supports silent functionality
 *
 * @param players list of the players
 * @param silent whether or not the game is silent
 */
Game::Game(std::vector<Player *> players, bool silent) {
    this->players = players;
    this->silent = silent;
}

/**
 *
 * destructor
 *
 * main point of this is to free the player pointers
 *
 */
Game::~Game() {
    for (auto player : players){
        free(player);
        player = NULL;
    }
}

//
// methods
//

/**
 *
 * checks to see if two vectors are equal
 *
 * @tparam T type of vector
 * @param v1 first vector
 * @param v2 second vector
 * @return are they equal
 */
template<typename T>
bool isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
    return (v1.size() == v2.size() &&
            std::equal(v1.begin(), v1.end(), v2.begin()));
}

/**
 *
 * starts the game
 *
 */
void Game::play() {

    inputHelp();

    int i = 0;

    while(!hasWinner()){
        takeTurn(players[i++ % players.size()]);
    }

    // take one extra turn
    for(int extTurn = i - 1 + players.size(); i < extTurn; i++){
        takeTurn(players[i % players.size()]);
    }

    Player* winner;

    int highScore = 0;

    printStdBreak();

    // print the scores
    for (auto player : players){
        std::cout << player->status() << std::endl;

        if (player->getScore() >= highScore){
            winner = player;
            highScore = winner->getScore();
        }
    }

    printStdBreak();

    std::cout << winner->getName() << " has won the game!" << std::endl;

}

/**
 *
 * take a single turn with a player
 *
 * @param player
 */
int Game::takeTurn(Player* player) {

    // declare variables
    bool stillGoing;

    int numDice = 6;
    int scoredPoints = 0;

    std::vector<int> rolls;
    std::vector<int> chosenDice;

    if (not silent){
        printStdBreak();

        // print a turn starting message
        std::cout << player->getName() << " is starting their turn" << std::endl;

        for (auto playerTemp : players){
            std::cout << playerTemp->status() << std::endl;
        }

    }

    do {

        rolls = std::vector<int>(numDice);

        dice.rollDice(&rolls);

        if (getLegalMoves(&rolls).size() == 0){

            // we encountered a farkle

            if (not silent){
                printStdBreak();


                std::cout << "Oh no! " << player->getName() << " farkled!" << std::endl;
                std::cout << player->getName() << " scores no points this round!"
                                                                            << std::endl;

                printStdBreak();
            }


            scoredPoints = 0; // we score 0 points this round
            break;
        }

        do {
            chosenDice = player->chooseDice(&rolls, scoredPoints);
        } while (chosenDice.size() == 0);

        // take the chosen dice out of the pool of dice to roll
        numDice -= chosenDice.size();
        // score those dice
        scoredPoints += scoreRoll(&chosenDice);

        // if the selected dice include all of the dice listed, we are not still going
        stillGoing = !isEqual(chosenDice, rolls);

    } while (stillGoing);

    player->scorePoints(scoredPoints);

    if (not silent){
        std::cout <<  player->getName() + " scored " << scoredPoints <<
                                                    " points!" << std::endl;
    }

    return scoredPoints;

}

/**
 *
 * does the game have a winner
 *
 * @return true if the game has a winner
 */
bool Game::hasWinner() {
    bool over = false;

    for (auto player : players){
        over = over || player->getScore() >= GAME_END;
    }

    return over;
}
