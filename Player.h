//
// Created by arthur wesley on 9/21/20.
//

#include <vector>
#include <string>

#ifndef UNTITLED1_PLAYER_H
#define UNTITLED1_PLAYER_H


class Player {
public:

    explicit Player(std::string name);

    void scorePoints(int points);

    int getScore();

    bool isSilent();
    bool isInGame();

    virtual std::vector<int> chooseDice(std::vector<int>* dice, int storedScore);

    std::string status();
    std::string getName();

protected:
    int score;

    bool silent = false;
private:
    std::string name;
};


#endif //UNTITLED1_PLAYER_H
