#include <string>
#include <iostream>
#include "Player.h"

//1-Parameter Player constructor which defines the name of the player...

Player::Player() {
    this->name = new string("Default Name");
    this->dice = new Dice();
    this->isTurn = new bool(false);
}
Player::Player(std::string* name) {
    this->name = new string(*name);
    this->dice = new Dice();
    this->isTurn = new bool(false);
//    this->handOfCards = new Hand();
}

//Destructor for Player Class.
Player::~Player() {
    delete this->dice;
    delete this->name;
    delete this->isTurn;
    this->isTurn = nullptr;
//    delete handOfCards;
    this->dice = nullptr;
    this->name = nullptr;
//    handOfCards = nullptr;
}

//This method calls the Roll() method of the Player's Dice Object.
void Player::RollDice() {
    int numDice;

    std::cout << "Enter number of dice to roll: (Greater than 3 will result in 3 dice, less than 1 will result in 1 dice)" << std::endl;
    std::cin >> numDice;

    this->setNumDice(numDice);

    this->getDice()->Roll();
}

void Player::showDiceFrequency() {
    this->getDice()->printFrequency();
}

void Player::showDiceValuePercentage() {
    this->getDice()->displayPercentage();
}


bool Player::canAttack() {
    return *(this->getIsTurn()); // && number of armies on the country >= 2
}

void Player::fortify() {
    std::cout << *this->getName() << " is fortifying..." << std::endl;

    std::cout << std::endl;
}

void Player::attack() {
    std::cout << *this->getName() <<" is attacking..." << std::endl;

    std::cout << std::endl;
}

void Player::reinforce() {
    std::cout << *this->getName() << " is reinforcing..." << std::endl;

    std::cout << std::endl;
}

//=================
//BEGIN Getters and Setters
//=================
std::string *Player::getName() const {
    return name;
}

int Player::getHighestRoll() const {
    return *this->getDice()->getHighestRoll();

}

//Hand *Player::getHand() const {
//    std::cout << "Returning the hand of cards" << std::endl;
//}

Dice *Player::getDice() const {
    return dice;
}

void Player::setNumDice(int numDice) {
    this->getDice()->setNumDice(numDice);
}

void Player::setIsTurn(bool value) {
    this->isTurn = &value;
}

bool *Player::getIsTurn() const {
    return this->isTurn;
}
//=================
//END Getters and Setters
//=================

int playerDriver() {
//    std::string player1Name;
//    std::string player2Name;

    //=================
    //PLAYER 1
    //=================
//    std::cout << "Enter player 1's name: " << std::endl;
//    std::cin >> player1Name;

    auto player1 = new Player();

    std::cout << "Demonstrating that " << *player1->getName() << " has cards." << std::endl;
//    player1->getHand();


    std::cout << "===============================" << std::endl;
    std::cout << std::endl;

    player1->RollDice();

    std::cout << "============Frequency============="<< std::endl;

    player1->showDiceFrequency();

    std::cout << "============Percentage============"<< std::endl;

    player1->showDiceValuePercentage();

    std::cout << "============Player Actions============"<< std::endl;
    player1 -> attack();
    player1 -> reinforce();
    player1 -> fortify();

    delete player1;
    player1 = nullptr;

    return 0;
}

int main() {
playerDriver();
}
