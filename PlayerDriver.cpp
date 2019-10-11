
#include <iostream>
#include "Player.h"

int main() {
    std::string player1Name;
    std::string player2Name;
    int numDice;

    //=================
    //PLAYER 1
    //=================
    std::cout << "Enter player 1's name: " << std::endl;
    std::cin >> player1Name;

    auto player1 = new Player(&player1Name);

    std::cout << "Demonstrating that " << *player1->getName() << " has cards." << std::endl;
    player1->getHand();

    std::cout << "Enter number of dice to roll: (Greater than 3 will result in 3 dice, less than 1 will result in 1 dice)" << std::endl;
    std::cin >> numDice;

    player1->setNumDice(numDice);

    std::cout << "Rolling the " << *player1->getDice()->getNumDice() << " dice, 10 times." << std::endl;

    std::cout << "===============================" << std::endl;
    std::cout << std::endl;

    for(int i = 0; i< 10; i++) {
        std::cout << "Roll " << (i+1) << ": " <<  std::endl;
        player1->RollDice();

        std::cout << std::endl;
    }


    std::cout << "============Frequency============="<< std::endl;

    player1->getDice()->printFrequency();

    std::cout << "============Percentage============"<< std::endl;

    player1->getDice()->displayPercentage();

    std::cout << "============Player Actions============"<< std::endl;
    player1 -> attack();
    player1 -> reinforce();
    player1 -> fortify();

    delete player1;
    player1 = nullptr;

    //=================
    //PLAYER 2
    //=================

    auto player2 = new Player(&player2Name);

    std::cout << "Enter player 2's name: " << std::endl;
    std::cin >> player2Name;

    std::cout << "Enter number of dice to roll: (Greater than 3 will result in 3 dice, less than 1 will result in 1 dice)" << std::endl;
    std::cin >> numDice;

    player2->setNumDice(numDice);

    std::cout << "Rolling the " << *player2->getDice()->getNumDice() << " dice, 10 times." << std::endl;

    std::cout << "===============================" << std::endl;
    std::cout << std::endl;

    for(int i = 0; i< 10; i++) {
        std::cout << "Roll " << (i+1) << ": " <<  std::endl;
        player2->RollDice();

        std::cout << std::endl;
    }


    std::cout << "============Frequency============="<< std::endl;

    player2->getDice()->printFrequency();

    std::cout << "============Percentage============"<< std::endl;

    player2->getDice()->displayPercentage();

    std::cout << "============Player Actions============"<< std::endl;
    player2 -> attack();
    player2 -> reinforce();
    player2 -> fortify();

    delete player2;
    player2 = nullptr;



    return 0;
}