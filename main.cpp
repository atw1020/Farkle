#include <iostream>
#include <vector>
#include "scorer.h"
#include "IO.h"
#include "Player.h"
#include "Game.h"
#include "AI.h"
#include "stats.h"

/**
 *
 * test program for the scorer
 *
 */
void testScorer(){
    std::vector<std::vector<int>> tests = {
            {1, 2, 3, 3, 5, 6},
            {1, 2, 3, 4, 5, 6},
            {1, 1, 1, 4, 2, 6},
            {2, 2, 2, 4, 3, 6},
            {6, 6, 6, 6, 6, 6},
            {1, 1, 1, 1, 1, 6},
            {5, 5, 5, 5, 2, 1},
            {6, 6, 6, 2, 2, 2},
            {1, 1, 5, 5, 2, 2},
            {2, 2, 3},
            {1, 2, 2},
            {4, 4, 4, 4, 1, 1}
    };

    int results[] = {
            150,
            1500,
            300,
            200,
            3000,
            2000,
            1100,
            2500,
            1500,
            0,
            100,
            1500
    };

    int score;

    for(int i = 0; i < tests.size(); i++){

        int numDice = tests[i].size();
        score = scoreRoll(&tests[i]);

        std::cout << "number rolled: ";

        for (int die : tests[i]){
            std::cout << die << " ";
        }

        std::cout << std::endl;

        std::cout << "Score was " << score << std::endl;

        if(results[i] != score){

            std::cout << "Error in testing roll " << rollString(&tests[i]);

            std::cout << "was " << score << " and Should have been " << results[i] << std::endl;
        }

        // test printing the scoring rolls out

        std::vector<std::vector<int>> legalMoves = getLegalMoves(&tests[i]);



        std::cout << std::endl;

    }

}

int main() {

    /*
    Game game({
              new Player("Mom"),
              new Player("Dad"),
              new Player("Lucas"),
              new AI(HARD),
              // new AI(MEDIUM, true),
              // new AI(EASY, true),
    });
     */


    Game game({
        new Player("Arthur"),
        new AI(BRUTAL),
        new AI(HARD),
        new AI(MEDIUM),
        new AI(EASY)
    });

    //Game game({"Arthur", "Lucas"});
    game.play();


    return 0;
}
