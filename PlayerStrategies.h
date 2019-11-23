#pragma once
#include <iostream>
//#include"GameObservers.h"
using namespace std;

class Player;

class Strategy {

public:

    virtual void executeReinforce(Player* player) = 0;
    virtual void executeFortify(Player* player) = 0;
    virtual void executeAttack(Player* player) = 0;


};

class AggressivePlayer : public Strategy {

public:
    void executeReinforce(Player* player);
    void executeFortify(Player* player);
    void executeAttack(Player* player);

};

class HumanPlayer : public Strategy {
public:
    void executeReinforce(Player* player);
    void executeFortify(Player* player);
    void executeAttack(Player* player);
};

class BenevolentPlayer : public Strategy {
public:
    void executeReinforce(Player* player);
    void executeFortify(Player* player);
    void executeAttack(Player* player);

};

class RandomPlayer : public Strategy {
public:
	void executeReinforce(Player* player);
	void executeFortify(Player* player);
	void executeAttack(Player* player);

};

class CheaterPlayer : public Strategy {
public:
	void executeReinforce(Player* player);
	void executeFortify(Player* player);
	void executeAttack(Player* player);

};

int stratDriver();
