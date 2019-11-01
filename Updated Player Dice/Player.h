//
// Created by Christopher Diktakis on 2019-10-26.
//
#pragma once

#include <iostream>
#include <vector>
#include "Dice.h"
//#include "Cards.h"

class Player {
private:
    std::string* name;
    Dice* dice;
    bool* isTurn;
//    Hand *handOfCards;
//    vector<Country> *countries;

public:
    Player(std::string* name);
    Player();
    ~Player();

    void showDiceFrequency();
    void showDiceValuePercentage();
    void reinforce();
    void attack();
    void fortify();
    void RollDice();
    void setNumDice(int numDice);
    void setIsTurn(bool value);
    int getHighestRoll() const;
    bool *getIsTurn() const;
    bool canAttack();
    bool isDefending();


    Dice *getDice() const;
    std::string *getName() const;
//    Hand *getHand() const;
    int playerDriver();

};





