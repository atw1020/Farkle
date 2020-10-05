//
// Created by arthur wesley on 9/27/20.
//

#ifndef FARKLE_STATS_H
#define FARKLE_STATS_H

#include <map>


std::map<int, double> scorePMFTable(int numDice);
double scoreCMF(int value, std::map<int, double> *table);
void testBreak500();

#endif //FARKLE_STATS_H