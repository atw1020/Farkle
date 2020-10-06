//
// Created by arthur wesley on 9/21/20.
//


#ifndef UNTITLED1_AI_H
#define UNTITLED1_AI_H

#include <array>
#include "Player.h"
#include <map>
#include "stats.h"

enum Difficulty {EASY, MEDIUM, HARD, BRUTAL, FIRST_TURN};

class AI : public Player{
public:

    AI(Difficulty difficulty);

    AI(Difficulty difficulty, bool silent);

    std::vector<int> chooseDice(std::vector<int>* dice, int storedScore) override;

private:
    const std::array<double, 6> farkleOdds = {
            0.666667,
            0.444444,
            0.277778,
            0.157407,
            0.0771605,
            0.0231481
    };
    const std::array<double, 6> expectedScores = {
            75,
            90,
            115.705,
            157.509,
            220.283,
            397.742
    };

    static const std::array<std::array<double, NUM_SCORES>, 6> lookupTables;

    static int IDCounter;

    double expectedValue(int numDice, int currentScore);

    std::vector<int> break500(std::vector<int>* dice, int storedScore);
    std::vector<int> expectedValueChoose(std::vector<int> * dice, int storedScore);

    Difficulty difficulty;

    std::vector<int> randomMove(std::vector<int> *dice, int storedScore);
};


#endif //UNTITLED1_AI_H
