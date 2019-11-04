#include <string>
#include <iostream>
#include <random>
#include <vector>
#include "Player.h"

//https://github.com/armandorusso/Risk-Domination.git

//1-Parameter Player constructor which defines the name of the player...
Player::Player(std::string name, Map &map) {
	this->name = new string(name);
	this->dice = new Dice();
	this->handOfCards = new Hand();
	countriesKey = new vector<int>();
	numberOfCountries = new int(0);
	this->map = map;


}

//Destructor for Player Class.
Player::~Player() {

	delete[] countriesKey;
	delete dice;
	delete name;
	delete numberOfCountries;
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

	std::cout << *name << " is fortifying..." << std::endl;

	std::cout << std::endl;
}

void Player::attack() {
	std::cout << *name << " is attacking..." << std::endl;

	std::cout << std::endl;
}

void Player::reinforce() {
	std::cout << this->getName() << " is reinforcing..." << std::endl;

	int armiesToExchange = 0;

	//GET ARMIES FOR COUNTRIES
	armiesToExchange = this->getNumOfCountries() / 3;

	//Must get minimum 3 armies
	if (armiesToExchange < 3) {
		armiesToExchange = 3;
	}

	//GET ARMIES FROM CONTINENT-CONTROL VALUE
	/*if (this->checkIfOwnCont()) {
		std::cout << "player owns a continent";
	  armiesToExchange = armiesToExchange + 5;
	}*/

	//EXCHANGE CARDS FOR ARMIES
	while (this->getHand()->exchange()) {
		armiesToExchange = armiesToExchange + *this->getHand()->getNumArmies();
	}

	std::cout << "Armies to exchange: " << armiesToExchange << std::endl;
	std::cout << std::endl;


	std::cout << "Placing armies in owned countries..." << std::endl;
	int index = 0;
	while (armiesToExchange != 0) {
		if (index == this->getCountries().size()) {
			index = 0;
		}

		this->map.getCountryArray()[this->getCountries().at(index)].addArmy(1);
		std::cout << "Country " << index << ": " << this->map.getCountryArray()[this->getCountries().at(index)].getArmy() << std::endl;

		armiesToExchange--;
		index++;
	}
}

void Player::addCountry(int key) {
	countriesKey->push_back(key);
	(*numberOfCountries)++;
}

void Player::removeCountry(int key) {
	int x = countriesKey->size();
	for (int i = 0; i < x; i++) {

		if (countriesKey->at(i) == key) {
			countriesKey->erase(countriesKey->begin() + i);
			*numberOfCountries -= 1;
		}

	}

}
bool Player::checkIfOwnCont() {

	Continent* arrayCont = map.getContinentArray();
	Country* arrayCountry = map.getCountryArray();
	int  x = map.getContinentCount();

	int* arr = new int[x];
	for (int i = 0; i < x; i++) {
		arr[i] = 0;
	}

	for (int i = 0; i < *numberOfCountries; i++) {
		int key = countriesKey->at(i);
		int continentKey = arrayCountry[key].getContinentKey();

		arr[key]++;

	}

	for (int i = 0; i < x; i++) {
		if (arr[i] == arrayCont[i].getCountryNum()) {
			arrayCont->setConquered(true);
			arrayCont[i].setOwner(*name);
			return true;
		}
	}
	return false;
	delete[] arr;
}
//=================
//BEGIN Getters and Setters
//=================
std::string Player::getName() const {
	return *name;
}

Hand* Player::getHand() const {
	return handOfCards;
}

Dice* Player::getDice() const {
	return dice;
}

void Player::setNumDice(int numDice) {
	this->getDice()->setNumDice(numDice);
}
//=================
//END Getters and Setters
//=================