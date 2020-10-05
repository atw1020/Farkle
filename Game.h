//
// Created by arthur wesley on 9/21/20.
//

#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#include "vector"
#include "Player.h"
#include <string>
#include "die.h"

class Game {
public:
    Game(std::vector<std::string> names);
    Game(std::vector<Player*> players);
    Game(std::vector<Player*> players, bool silent);

    ~Game();

    int takeTurn(Player* player);

    void play();
private:

    die dice;

    std::vector<Player*> players;

    bool hasWinner();
    bool silent = false;
};


#endif //UNTITLED1_GAME_H
