#include <iostream>
#include <vector>
#include "Dice.h"
#include "Cards.h"

#ifndef INC_345PROJECT_PLAYER_H
#define INC_345PROJECT_PLAYER_H

class Player {

private:
    std::string* name;
    Dice* dice;
    Hand *handOfCards;
//    vector<Country> *countries;

public:
    Player(std::string* name);
    ~Player();

    void reinforce();
    void attack();
    void fortify();
    void RollDice();
    void setNumDice(int numDice);

    std::string *getName() const;

    Dice *getDice() const;
    Hand *getHand() const;

};

#endif //INC_345PROJECT_PLAYER_H
