//
// Created by arthur wesley on 8/28/20.
//

#include <array>
#include <vector>
#include "scorer.h"

#define NUM_ROLLS 6

/**
 *
 * scores a given roll of an arbitrary number of die
 *
 * @param dice the values of the die of a given roll
 * @param numDice number of die in the array
 * @return
 */
int scoreRoll(std::vector<int>* dice){

    int score = 0;
    std::array<int, NUM_ROLLS> rollCounts = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < dice->size(); i++){
        // subtract one from the roll number to get the index
        rollCounts[(*dice)[i] - 1]++;
    }



    bool straight = true;

    int triplets = 0;
    int pairs = 0;

    switch (dice->size()){

        case 6:
            // go through all the die

            for(int i = 0; i < NUM_ROLLS; i++){

                // check to see if a straight is still valid
                straight = straight && (rollCounts[i] == 1);

                // check for 6 of a kind
                if(rollCounts[i] == 6){

                    // score
                    score += 3000;

                    break;
                }

                // check for triplets
                if(rollCounts[i] == 3){

                    // we have a new triplet
                    triplets++;

                    // if we have two triplets
                    if(triplets == 2){

                        // we have 2 triplets, score 2500
                        score += 2500;

                        // exit the loop
                        break;
                    }
                }

                // check for pairs
                if(rollCounts[i] == 2){

                    pairs++;

                    // if we have three pairs
                    if(pairs == 3){
                        // we have 3 pairs, score 1500
                        score += 1500;

                        // exit the loop
                        break;
                    }
                }

                // if we have 4 of a kind that counts as two pairs
                if(rollCounts[i] == 4){

                    pairs += 2;

                    // if we have three pairs
                    if(pairs == 3){
                        // we have 3 pairs, score 1500
                        score += 1500;

                        // exit the loop
                        break;
                    }
                }
            }

            // if we have a straight, score 1500
            if(straight){
                score += 1500;
            }

            if(score != 0){
                // if we scored anything with 6 die, we don't need to do any more scoring, so don't
                // fall through
                break;
            }
        case 5:
            // check for 5 of a kind
            for(int i = 0; i < NUM_ROLLS; i++){

                if(rollCounts[i] == 5){
                    // consume the die
                    rollCounts[i] -= 5;

                    // we have 5 of a kind, score 2000
                    score += 2000;

                    // exit the loop
                    break;
                }
            }
        case 4:
            // check for 4 of a kind
            for(int i = 0; i < NUM_ROLLS; i++){

                if(rollCounts[i] == 4){
                    // consume the die
                    rollCounts[i] -= 4;

                    // we have 4 of a kind, score 2000
                    score += 1000;

                    // exit the loop
                    break;
                }
            }
        case 3:
            // check for 3 of a kind
            // note: i starts at 1 instead of zero b/c ones are ignored for 3 of a kind
            for(int i = 1; i < NUM_ROLLS; i++){

                if(rollCounts[i] == 3){
                    // score points for the 3 of a kind
                    score += 100 * (i + 1);

                    // consume the die
                    rollCounts[i] -= 3;
                }
            }
        default:
            // add 100 per 1 and 50 per 5
            score += 100 * rollCounts[0] + 50 * rollCounts[4];
    }

    return score;
}

/**
 *
 * creates a vector containing all the legal vectors of moves
 *
 * @param dice dice that were rolled
 * @return list of all scoring dice **SORTED BY AVERAGE POINTS PER DIE**
 */
std::vector<std::vector<int>> getLegalMoves(std::vector<int>* dice){

    std::vector<std::vector<int>> legalMoves;
    std::array<int, NUM_ROLLS> rollCounts = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < dice->size(); i++){
        // subtract one from the roll number to get the index
        rollCounts[(*dice)[i] - 1]++;
    }

    bool straight = true;

    int triplets = 0;
    int pairs = 0;

    switch (dice->size()){

        case 6:
            // go through all the die

            for(int i = 0; i < NUM_ROLLS; i++){

                // check to see if a straight is still valid
                straight = straight && (rollCounts[i] == 1);

                // check for 6 of a kind
                if(rollCounts[i] == 6){

                    // all of the dice an be scored
                    legalMoves.push_back(*dice); // return all dice

                    break;
                }

                // check for triplets
                if(rollCounts[i] == 3){

                    // we have a new triplet
                    triplets++;

                    // if we have two triplets
                    if(triplets == 2){

                        // we have 2 triplets
                        legalMoves.push_back((*dice));

                        // exit the loop
                        break;
                    }
                }

                // check for pairs
                if(rollCounts[i] == 2){

                    pairs++;

                    // if we have three pairs
                    if(pairs == 3){
                        // we have 3 pairs, score 1500
                        legalMoves.push_back((*dice));

                        // exit the loop
                        break;
                    }
                }

                // if we have 4 of a kind that counts as two pairs
                if(rollCounts[i] == 4){

                    pairs += 2;

                    // if we have three pairs
                    if(pairs == 3){
                        // we have 3 pairs, score 1500
                        legalMoves.push_back((*dice));

                        // exit the loop
                        break;
                    }
                }
            }

            // if we have a straight, score 1500
            if(straight){
                legalMoves.push_back((*dice));
            }

            if(!legalMoves.empty()){
                // if we scored anything with 6 die, we don't need to do any more scoring, so don't
                // fall through
                break;
            }
        case 5:
            // check for 5 of a kind
            for(int i = 0; i < NUM_ROLLS; i++){

                if(rollCounts[i] == 5){
                    // consume the die
                    rollCounts[i] -= 5;

                    // we have 5 of a kind, score 2000
                    legalMoves.push_back({i + 1, i + 1, i + 1, i + 1, i + 1});

                    // exit the loop
                    break;
                }
            }
        case 4:
            // check for 4 of a kind
            for(int i = 0; i < NUM_ROLLS; i++){

                if(rollCounts[i] == 4){
                    // consume the die
                    rollCounts[i] -= 4;

                    // we have 4 of a kind, score 2000
                    legalMoves.push_back({i + 1, i + 1, i + 1, i + 1});

                    // exit the loop
                    break;
                }
            }
        case 3:
            // check for 3 of a kind
            // note: i starts at 1 instead of zero b/c ones are ignored for 3 of a kind
            // note: i starts at 2 instead of 1 because we check for 2 of a kind later
            //       to be sure that the results are sorted correctly
            for(int i = 2; i < NUM_ROLLS; i++){

                if(rollCounts[i] == 3){
                    // score points for the 3 of a kind
                    legalMoves.push_back({i + 1, i + 1, i + 1});

                    // consume the die
                    rollCounts[i] -= 3;
                }
            }
        default:
            // add 100s
            for (int i = 0; i < rollCounts[0]; i++){
                legalMoves.push_back({1});
            }

            // add 200s
            if(rollCounts[1] == 3){
                // score points for the 3 of a kind
                legalMoves.push_back({2, 2, 2});

                // consume the die
                rollCounts[2] -= 3;
            }

            // add 50s
            for (int i = 0; i < rollCounts[4]; i++){
                legalMoves.push_back({5});
            }
    }

    return legalMoves;

}


