//
// Created by arthur wesley on 9/1/20.
//

#include "die.h"

#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

/**
 *
 * initalizes random number generator
 *
 */
die::die(){
    srand(time(NULL));
}

/**
 *
 * rolls a single die
 *
 * @return: random number 1 to 6
 */
int die::rollDie(){
    return rand() % 6 + 1;
}

/**
 *
 * rolls multiple die and places them in the die array
 *
 * @param dice the array being modified
 * @param numDice number of die to roll
 */
void die::rollDice(std::vector<int>* rolls){
    for(int i = 0; i < rolls->size(); i++){
        (*rolls)[i] = rollDie();
    }
}