#include <iostream>
#include "PlayerStrategies.h"

using namespace std;

//Reinforces strongest country. Always attacks with it until unable
void AggressivePlayer::execute() {
    cout << "Aggressive Player: Execute()" << endl;
}

//Human interacts with it.
void HumanPlayer::execute() {
    cout << "Human Player: Execute()" << endl;
}


//Reinforces weakest countries
//Never atacks
//Fortifies in order to move armies to weaker countries.
void BenevolentPlayer::execute() {
    cout << "Benevolent Player: Execute()" << endl;
}

int stratDriver() {

    return 0;
}

//Driver should demonstrate:

//Different players can be assigned different strategies.
//Should be able to switch between these strategies at any time.

//Notes:
/*
 * Add Strategy Object to Player class
 * Private:
 *  Strategy *strategy;
 *
 *
 *
 * Public:
 *
 * void setStrategy() {
 *
 * }
 *
 * int executeStrategy() {
 * return this->strategy->execute();
 *
 * void setStrategy(Strategy *newStrategy) {
 * this->strategy = newStrategy
 * }
 */



