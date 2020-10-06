//
// Created by arthur wesley on 9/27/20.
//

#include "stats.h"
#include <vector>
#include <array>
#include <iostream>
#include "die.h"
#include "scorer.h"
#include "Game.h"
#include "AI.h"

#define NUM_REPS 10

/**
 *
 * takes a given roll of 6 dice and gets the next legal roll
 * this basically makes it a hexal number
 *
 * @param rolls
 */
void nextRoll(std::vector<int>* rolls){

    int index = 0;

    // increment the LSH
    (*rolls)[index]++;

    // update more significant hexits when needed
    while((*rolls)[index++] > 6){
        (*rolls)[index]++;
        (*rolls)[index - 1] -= 6;
    }

}

/**
 *
 * cumulative mass function of the score
 *
 * @param value value to evaluate the PMF at
 * @param table table to look up the result in
 * @return Cumulative Probability Mass function of the score up to value (inclusive)
 */
double scoreCMF(int value, std::array<double, NUM_SCORES>* table){

    double acc;

    assert(value % 50 == 0);

    // loop through the table until you reach scores higher than the indicated value
    for (int i = 0; i <= value / 50; i++){
        acc += (*table)[i];
    }

    return acc;

}

/**
 *
 * probability mass function of the score for the given number of dice
 *
 * @param numDice number of dice to get the PMF for
 * @return a PMF table for that number of dice
 */
std::array<double, NUM_SCORES> scorePMF(int numDice){

    std::array<double, NUM_SCORES> PMF{};
    std::vector<int> dice = std::vector<int>(1);

    int score;
    int combos = pow(6, numDice);

    // go through all the possible rolls
    for (int i = 0; i < combos; i++){

        // score the roll
        score = scoreRoll(&dice);

        // increment the entry in the table
        PMF[score / 50]++;

        // get the next roll
        nextRoll(&dice);

    }
    // convert the counts to odds by dividing by

    for (int i = 0; i < NUM_SCORES; i++){
        PMF[i] /= combos;
    }

    return PMF;

}

/**
 *
 * scores every possible dice combination
 *
 */
void scoreAllRolls(){

    std::vector<int> rolls;
    long int scoreAcc;
    long int score, farkles;

    int currentReps;

    // allocate rolls

    for(int i = 0; i < 6; i++){

        scoreAcc = 0;
        farkles = 0;

        rolls = std::vector<int>(i + 1, 1);
        currentReps = (int) pow(6, i + 1);

        for(int j = 0; j < currentReps; j++){

            // get the next roll and score it
            nextRoll(&rolls);
            score = scoreRoll(&rolls);

            // accumulate the score
            scoreAcc += score;
            if (score == 0){
                farkles++;
            }

        }

        std::cout << "Rolled " << i + 1 << " Dice and rolled them "
                  << currentReps << " times. " << std::endl
                  << "- On average, each roll scored "
                  << (float) scoreAcc / currentReps << std::endl
                  << "- A farkle was rolled " << (float) farkles / currentReps
                  << "% of the time. " << std::endl
                  << "- When a farkle was not rolled, the average score was "
                  << (float) scoreAcc / (currentReps - farkles)
                  << std::endl << std::endl;
    }

}

void scoreRandomRolls(){

    std::vector<int> rolls = {0, 0, 0, 0, 0, 0};
    long int scoreAcc;
    long int score, farkles;
    die dice;

    // allocate rolls

    for(int i = 0; i < 6; i++){

        scoreAcc = 0;
        farkles = 0;

        rolls = std::vector<int>(i + 1);

        // average across 10000 rolls
        for(int j = 0; j < NUM_REPS; j++){

            // roll the die
            dice.rollDice(&rolls);

            score = scoreRoll(&rolls);

            // accumulate the score
            scoreAcc += score;
            if (score == 0){
                farkles++;
            }

        }

        std::cout << "Rolled " << i + 1 << " Dice and rolled them " << NUM_REPS
                  << " times. " << std::endl
                  << "- On average, each roll scored "
                  << (float) scoreAcc / NUM_REPS << std::endl
                  << "- A farkle was rolled " << (float) farkles / NUM_REPS
                  << "% of the time. " << std::endl
                  << "- When a farkle was not rolled, the average score was "
                  << (float) scoreAcc / (NUM_REPS - farkles)
                  << std::endl << std::endl;
    }
}

void testBreak500(){

    Player* control = new AI(HARD, true);
    Player* treatment = new AI(FIRST_TURN, true);

    Game test({
        control,
        treatment
    }, true);

    double breakRate;

    int lastScore;

    for (int i = 0; i < NUM_REPS; i++){
        lastScore = test.takeTurn(control);

        if (lastScore >= 500){
            breakRate++;
        }
    }

    std::cout << "the control AI broke 500 " <<
                breakRate * 100 / NUM_REPS << "% of the time\n";

    breakRate = 0;

    for (int i = 0; i < NUM_REPS; i++){
        lastScore = test.takeTurn(treatment);

        if (lastScore >= 500){
            breakRate++;
        }
    }

    std::cout << "the test AI broke 500 " <<
              breakRate * 100 / NUM_REPS << "% of the time\n";

}