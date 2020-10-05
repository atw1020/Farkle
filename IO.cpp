//
// Created by arthur wesley on 9/21/20.
//

#include <iostream>
#include "IO.h"
#include "scorer.h"
#include <unordered_set>

/**
 *
 * gets a string that represents a roll
 *
 * @param dice: die to convert to a string
 * @return String representation of a roll
 */
std::string rollString(std::vector<int>* dice){

    std::string roll = "";

    for(int j = 0; j < dice->size(); j++){
        roll = roll + std::to_string((*dice)[j]) + " ";
    }

    return roll;

}

std::string getKeptDice(){
    std::string in = "";

    // prompt the user and get the input
    std::cout << "enter the moves you would like to select: ";
    std::cin >> in;

    return in;
}

/**
 *
 * gets and parses input from the user about what dice to keep
 *
 * @param dice the dice to parse the input for
 * @return list of all the dice to be scored
 */
std::vector<int> parse_input(std::vector<int>* dice){

    std::string input = getKeptDice();
    std::vector<std::vector<int>> legalMoves = getLegalMoves(dice);

    std::vector<int> keptDice;

    if (input == "a"){
        return *dice;
    }

    // make a set of the input string
    std::unordered_set<char> options;

    for (char option : input){
        options.insert(option);
    }

    // go through all of the options and add them to the kept dice
    for (char option: options){
        // check to see if the option is in range
        if (option - 'b' >= 0 && option - 'b' < legalMoves.size()){
            for (int dice : legalMoves[option - 'b']){
                keptDice.push_back(dice);
            }
        }
        else{
            // print the help message
            inputHelp();
            return std::vector<int>(); // return an empty vector to indicate a input error
        }
    }

    return keptDice;

}


/**
 *
 * prints a help message for the user
 *
 */
void inputHelp(){

    printStdBreak();

    std::cout << "Input the letter corresponding to each scoring die that you" << std::endl
              << "want to keep" << std::endl;

    printStdBreak();

    std::cout << "example:" << std::endl;

    std::vector<int> example = {1, 5, 4, 4, 3};

    printRollStatus(&example, 100);

    std::cout << "enter the moves you would like to select: bc" << std::endl;

    printStdBreak();

    std::cout << "to stop don't enter anything and press enter" << std::endl;

    std::cout << "Press any key to start the game..." << std::endl;

    std::string temp;
    std::cin >> temp;

}

/**
 *
 * prints a line of equals in order to indicate a break between sections
 *
 */
void printStdBreak(){
    std::cout << "==============================================================" << std::endl;
}

/**
 *
 * prints a status message for a given roll
 *
 * @param dice
 */
void printRollStatus(std::vector<int> *dice, int storedScore) {

    // break between items
    printStdBreak();

    // get a list of the legal moves
    std::vector<std::vector<int>> legalMoves = getLegalMoves(dice);

    // prompt the user for their selection
    std::cout << "rolled " << rollString(dice) << std::endl;

    std::cout << std::endl << "Legal Moves:" << std::endl;
    std::cout << "a) stop at " << storedScore + scoreRoll(dice) << " points" << std::endl;

    // show the player their options
    for (int i = 0; i < legalMoves.size(); i++){
        std::cout << (char) ( 'b' + i) << ") " << rollString(&legalMoves[i]) << "scores "
                  << scoreRoll(&legalMoves[i]) << " points" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "You currently have " << storedScore << " in the bank" << std::endl;

    // break between items
    printStdBreak();

}

void printNotInGame(Player* player, int points){
    std::cout << player->getName() << " did not score any points "
                                      "because they haven't reached 500 yet" << std::endl;
}