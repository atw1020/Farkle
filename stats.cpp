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

#define NUM_REPS 10000

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
 * probability mass function of the score
 *
 * @param value value to evaluate the PMF at
 * @param table table to look up the result in
 * @return Cumulative Probability Mass function of the score up to value (inclusive)
 */
double scoreCMF(int value, std::map<int, double>* table){

    double accumulator;

    for (auto entry : *table){
        if (entry.first <= value){
            accumulator += entry.second;
        }
    }

    return accumulator;

}

std::map<int, double> scorePMFTable(int numDice){

    std::map<int, double> table;

    int score;

    // initialize the dice
    std::vector<int> dice(numDice, 1);

    // go through all the dice combonations
    for (int i = 0; i < pow(6, numDice); i++){

        score = scoreRoll(&dice);

        // increment the count of this score
        if (table.find(score) != table.end()){
            table[score]++;
        }
        else{
            table[score] = 1;
        }

        // get the next roll
        nextRoll(&dice);
    }


    for (std::pair<int, double> entry : table){
        table[entry.first] = entry.second / pow(6, numDice);
    }

    return table;

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

    Player* control = new AI(HARD);
    Player* treatment = new AI(FIRST_TURN);

    Game test({
        control,
        treatment
    });

    double breakRate;

    int lastScore;

    for (int i = 0; i < NUM_REPS; i++){
        lastScore = test.takeTurn(control);

        if (lastScore >= 500){
            breakRate++;
        }
    }

    breakRate = 0;

    std::cout << "the control AI broke 500 " <<
                breakRate / NUM_REPS << "% of the time\n";

    for (int i = 0; i < NUM_REPS; i++){
        lastScore = test.takeTurn(treatment);

        if (lastScore >= 500){
            breakRate++;
        }
    }

    std::cout << "the test AI broke 500 " <<
              breakRate / NUM_REPS << "% of the time\n";

}