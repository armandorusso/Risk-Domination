#include <iostream>
#include "PlayerStrategies.h"

using namespace std;


void AggressivePlayer::executeAttack(Player *player) {

}

void AggressivePlayer::executeFortify(Player *player) {

}

void AggressivePlayer::executeReinforce(Player *player) {

}

void HumanPlayer::executeAttack(Player *player) {
//Add code here
}

void HumanPlayer::executeFortify(Player *player) {

}

void HumanPlayer::executeReinforce(Player *player) {

}

void BenevolentPlayer::executeAttack(Player *player) {

}

void BenevolentPlayer::executeFortify(Player *player) {

}

void BenevolentPlayer::executeReinforce(Player *player) {

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