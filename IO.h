//
// Created by arthur wesley on 9/21/20.
//

#ifndef UNTITLED1_IO_H
#define UNTITLED1_IO_H

#include <string>
#include <vector>
#include "Player.h"

std::string rollString(std::vector<int>* dice);
std::string getKeptDice();

std::vector<int> parse_input(std::vector<int>* dice);

void printStdBreak();
void inputHelp();
void printRollStatus(std::vector<int>* dice, int storedScore);
void printNotInGame(Player* player, int points);

#endif //UNTITLED1_IO_H
