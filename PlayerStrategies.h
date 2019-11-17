#pragma once
#include <iostream>
#include "Player.h"

using namespace std;

class Strategy {

public:
    virtual void executeReinforce(Player* player) = 0;
    virtual void executeFortify(Player* player) = 0;
    virtual void executeAttack(Player* player) = 0;


};

class AggressivePlayer : Strategy {

    void executeReinforce(Player* player);
    void executeFortify(Player* player);
    void executeAttack(Player* player);

};

class HumanPlayer : Strategy {

    void executeReinforce(Player* player);
    void executeFortify(Player* player);
    void executeAttack(Player* player);
};

class BenevolentPlayer : Strategy {

    void executeReinforce(Player* player);
    void executeFortify(Player* player);
    void executeAttack(Player* player);

};

int stratDriver();
