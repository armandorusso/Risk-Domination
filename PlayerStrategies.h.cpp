#include <iostream>
#include "PlayerStrategies.h"

using namespace std;


void AggressivePlayer::execute() {
    cout << "Aggressive Player: Execute()" << endl;
}

void HumanPlayer::execute() {
    cout << "Human Player: Execute()" << endl;
}

void BenevolentPlayer::execute() {
    cout << "Benevolent Player: Execute()" << endl;
}

int stratDriver() {

    return 0;
}

//Notes:
/*
 * Add Strategy Object to Player class
 * Private:
 *  Strategy *strategy;
 *
 * Public:
 * int executeStrategy() {
 * return this-.strategy->execute();
 */