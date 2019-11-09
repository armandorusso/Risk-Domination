#pragma once
#include <iostream>

using namespace std;

class Strategy {
    virtual void execute() = 0;
};

class AggressivePlayer : public Strategy {
    void execute() {
        cout << "Aggressive Player: Execute()" << endl;
    }
};

class HumanPlayer : public Strategy {
    void execute() {
        cout << "Human Player: Execute()" << endl;
    }
};

class BenevolentPlayer : public Strategy {
    void execute() {
        cout << "Benevolent Player: Execute()" << endl;
    }
};


//Notes:
/*
 * Add Strategy Object to Player class
 * Private:
 *  Strtegy *strategy;
 *
 * Public:
 * int executeStrategy() {
 * return this-.strategy->execute();
 *
 *
 */