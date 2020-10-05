#include <climits>
//
// Created by arthur wesley on 9/21/20.
//

#include "AI.h"
#include "scorer.h"
#include "IO.h"
#include <cfloat>
#include "stats.h"

int AI::IDCounter = 1;
/*
std::array<std::map<int, double>, 6> lookupTables = {
        scorePMFTable(1),
        scorePMFTable(2),
        scorePMFTable(3),
        scorePMFTable(4),
        scorePMFTable(5),
        scorePMFTable(6)
};
 */

//
// constructors
//

AI::AI(Difficulty difficulty) : Player("bot " + std::to_string(IDCounter++)) {
    this->difficulty = difficulty;
}

AI::AI(Difficulty difficulty, bool silent) : Player("bot " +
    std::to_string(IDCounter++)){
    this->difficulty = difficulty;
    this->silent = silent;
}

//
// methods
//

/**
 *
 * the AI's method to choose Dice based on expected value
 *
 * @param dice dice to choose from
 * @return the dice the AI has selected
 */
std::vector<int> AI::chooseDice(std::vector<int> *dice, int storedScore){

    // print a status
    if (not silent){
        printRollStatus(dice, storedScore);
    }

    std::vector<std::vector<int>> legalMoves = getLegalMoves(dice);
    std::vector<int> moves;

    switch(difficulty){
        case MEDIUM:

            // just always take the dice you get on your first roll
            moves = *dice;
            break;

        case EASY:

            // make random moves
            for (auto legalMove : legalMoves) {

                // condition for keeping the moves
                if (random() % 2 == 0){
                    // choose this move
                    for (auto dice : legalMove){
                        moves.push_back(dice);
                    }
                }
            }

            // if we didn't select any moves, stop at this point
            if (moves.size() == 0){
                moves = *dice;
            }

            break;

        case HARD:
            moves = expectedValueChoose(dice, storedScore);
            break;
        case FIRST_TURN:
            moves = break500(dice, storedScore);
            break;
    }

    return moves;
}

/**
 *
 * returns the move that has the highest expected score
 *
 * @param dice list of dice
 * @param storedScore the number of points we have in the bank
 * @return best possible move
 */
std::vector<int> AI::expectedValueChoose(std::vector<int> *dice, int storedScore) {

    double highestScore = scoreRoll(dice) + storedScore;
    int numDice = dice->size();

    std::vector<std::vector<int>> legalMoves = getLegalMoves(dice);
    std::vector<int> moves;

    double expectedScore;

    // go through each option
    for (auto legalMove : legalMoves){

        expectedScore = expectedValue(numDice - legalMove.size(),
                                  storedScore + scoreRoll(&legalMove));

        // if keeping the die has a higher expected value than our current score
        if (expectedScore > highestScore){
            // push this roll
            for (auto dice : legalMove){
                moves.push_back(dice);
            }

            // update the number of dice and highest score
            highestScore = expectedScore;

            // update the number of dice
            numDice -= legalMove.size();

        }

    }

    // if the highest expected value we have is the current dice,
    // return the dice to indicate that we are done
    if (fabs(highestScore - (storedScore + scoreRoll(dice))) < DBL_EPSILON){
        moves = *dice;
    }

    return moves;
}

/**
 *
 * returns the choice of dice that has the highest odds of breaking 500
 *
 * @param dice the dice to score
 * @param storedScore the score that we have in the bank
 * @return the move that has the highest odds of breaking 500
 */
std::vector<int> AI::break500(std::vector<int>* dice, int storedScore){

    std::vector<std::vector<int>> legalMoves = getLegalMoves(dice);

    std::vector<int> chosenDice;
    std::map<int, double> temp;

    // first thing is first, if we are already at or above 500, return all the dice
    if (scoreRoll(dice) + storedScore >= 500){
        return *dice;
    }

    int numDice = dice->size();
    int currentScore = storedScore;

    double bestOdds = 0;
    double odds;

    // go through all the possible combinations of dice

    for (auto move : legalMoves){

        numDice = numDice - move.size();

        // temp = lookupTables[numDice - 1];
        temp = scorePMFTable(numDice);

        odds = 1 - scoreCMF(500 - currentScore - scoreRoll(&move), &temp);

        if (odds > bestOdds){
            numDice -= move.size();
            bestOdds = odds;

            // add the dice

            for (auto die : *dice){
                chosenDice.push_back(die);
            }
        }
    }

    return chosenDice;

}

/**
 *
 * calculates the expected roll given a current score and number of Dice
 *
 * @param numDice number to dice to be rolled
 * @param currentScore our current score
 * @return the expected resulting score
 */
double AI::expectedValue(int numDice, int currentScore) {
    return (currentScore + expectedScores[numDice - 1]) *
            (1 - farkleOdds[numDice - 1]);
}

