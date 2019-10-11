#include <string>
#include <iostream>
#include <random>
#include <vector>
#include "Player.h"

//https://github.com/armandorusso/Risk-Domination.git

//1-Parameter Player constructor which defines the name of the player...
Player::Player(std::string* name) {
    this->name = new string(*name);
    this->dice = new Dice();
    this->handOfCards = new Hand();
}

//Destructor for Player Class.
Player::~Player() {
    delete dice;
    delete name;
    delete handOfCards;
    dice = nullptr;
    name = nullptr;
    handOfCards = nullptr;
}

//This method calls the Roll() method of the Player's Dice Object.
void Player::RollDice() {
    this->getDice()->Roll();
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

Hand *Player::getHand() const {
    std::cout << "Returning the hand of cards" << std::endl;
}

Dice *Player::getDice() const {
    return dice;
}

void Player::setNumDice(int numDice) {
    this->getDice()->setNumDice(numDice);
}
//=================
//END Getters and Setters
//=================


