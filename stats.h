//
// Created by arthur wesley on 9/27/20.
//

#ifndef FARKLE_STATS_H
#define FARKLE_STATS_H

#include <map>
#define NUM_SCORES 3000 / 50


std::array<double, NUM_SCORES> scorePMF(int numDice);
double scoreCMF(int value, const std::array<double, NUM_SCORES> *table);
void testBreak500();

#endif //FARKLE_STATS_H