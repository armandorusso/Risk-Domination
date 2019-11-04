#include <string>
#include <iostream>
#include "Player.h"
#include <vector>
#include <algorithm>

//1-Parameter Player constructor which defines the name of the player...

static vector<Player *> players;


//Outputs a title tag wit the given message.
void formatActionOutput(string message) {
	cout << "==================================================" << endl;
	cout << "\t\t" << message << endl;
	cout << "==================================================" << endl;
}

//Prints the contents of a vector of integers.
void printVector(vector<int> vector) {
	if (vector.size() != 0) {
		for (int i = 0; i< vector.size(); i++) {
			cout << vector[i] << endl;
		}
	}
	else {
		cout << "Nothing to print..." << endl;
	}

}

Player::Player() {
	this->name = new string("Default Name");
	this->dice = new Dice();
	this->isTurn = new bool(false);
	this->countries;

}

Player::Player(std::string name) {
	this->name = new string(name);
	this->dice = new Dice();
	this->isTurn = new bool(false);
	this->countries;
	this->handOfCards = new Hand();
}

//Destructor for Player Class.
Player::~Player() {
	delete this->dice;
	delete this->name;
	delete this->isTurn;
	delete this->handOfCards;
	this->isTurn = nullptr;
	this->dice = nullptr;
	this->name = nullptr;
	this->handOfCards = nullptr;

	for (int i = 0; i< countries.size(); i++) {
		delete countries[i];
		countries[i] = nullptr;
	}

	countries.clear();
}

//This method calls the Roll() method of the Player's Dice Object.
void Player::RollDice() {
	this->getDice()->Roll();
}

//This method prints the contents of a vector to the console.
void displayRoll(Player *player1, Player *player2) {
	vector<int> *player1CurrentRoll = player1->getDice()->getCurrentRoll();
	vector<int> *player2CurrentRoll = player2->getDice()->getCurrentRoll();

	std::cout << "====================" << std::endl;
	std::cout << "Rolling the dice" << std::endl;
	std::cout << "====================" << std::endl;

	std::cout << player1->getName() << "'s roll:";

	player1->getDice()->displayRolls(*player1CurrentRoll);

	std::cout << player2->getName() << "'s roll:";
	player2->getDice()->displayRolls(*player2CurrentRoll);
	std::cout << std::endl;

	std::cout << player1->getName() << "'s highest roll: " << player1->getHighestRoll() << std::endl;
	std::cout << player2->getName() << "'s highest roll: " << player2->getHighestRoll() << std::endl;

	std::cout << std::endl;
}

void Player::showDiceFrequency() {

	std::cout << "====================" << std::endl;
	std::cout << this->getName() << ": DICE FREQUENCY" << std::endl;
	std::cout << "====================" << std::endl;
	this->getDice()->printFrequency();
}

void Player::showDiceValuePercentage() {
	std::cout << "====================" << std::endl;
	std::cout << "DICE Percentage" << std::endl;
	std::cout << "====================" << std::endl;
	this->getDice()->displayPercentage();
}

//bool Player::canAttack() {
//    return this->getIsTurn(); // && number of armies on the country >= 2
//}
//
//bool Player::isDefending() {
//    return !(this->getIsTurn());
//}
//
//void Player::fortify() {
//    formatActionOutput(this->getName() + ": Fortification Phase");
//
//    std::cout << std::endl;
//}

void Player::attack() {
	this->setIsTurn(true);
	formatActionOutput(this->getName() + ": ATTACK PHASE");

	string answer;
	string attackingCountry;
	string defendingCountry;

	do {
		answer = "";
		attackingCountry = "";
		defendingCountry = "";

		cout << "Do you wish to attack? (y for yes, anything else for no)" << endl;
		cin >> answer;

		if (answer != "y") {
			break;
		}

		cout << "\nWhich country do you want to attack from?" << endl;
		cin >> attackingCountry;
		cout << "\nWhich country do you want to attack?" << endl;
		cin >> defendingCountry;

		formatActionOutput("ATTACKING " + defendingCountry);

		//Attacker rolls 1-3 dice, defender rolls 1-2 dice. #armies on respective countries minus 1.

		int numDice;

		std::cout << "Enter number of dice to roll: (Greater than 3 will result in 3 dice, less than 1 will result in 1 dice)" << std::endl;
		std::cin >> numDice;

		this->setNumDice(numDice);

	} while (answer == "y");

	cout << "Your attack phase is over." << endl;
}

void Player::reinforce() {
	std::cout << this->getName() << " is reinforcing..." << std::endl;

	int armiesToExchange = 0;

	//GET ARMIES FOR COUNTRIES
	armiesToExchange = this->getNumCountries() / 3;

	//Must get minimum 3 armies
	if (armiesToExchange < 3) {
		armiesToExchange = 3;
	}

	//GET ARMIES FROM CONTINENT-CONTROL VALUE
	//if (this->checkIfOwnCont()) {
	//	std::cout << "player owns a continent";
	//  armiesToExchange = armiesToExchange + controlValue;
	//}

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

		this->getCountries().at(index)->addArmy(1);
		std::cout << "Country " << index << ": " << this->getCountries().at(index)->getArmy() << std::endl;

		armiesToExchange--;
		index++;
	}
}

//Returns true if Player1's highest roll is greater than Player 2's roll. False otherwise.
bool compareRolls(Player *player1, Player *player2) {

	std::cout << "====================" << std::endl;
	std::cout << "RESULT" << std::endl;
	std::cout << "====================" << std::endl;
	if (player1->getHighestRoll() <= player2->getHighestRoll()) {
		std::cout << player1->getName() << " loses an army.\n" << std::endl;
		player1->loseArmy();
		return true;
	}
	else {
		std::cout << player2->getName() << " loses an army.\n" << std::endl;
		player2->loseArmy();
		return false;
	}
}

void Player::loseArmy() {
	//num Armies --;
}

//=================
//BEGIN Getters and Setters
//=================

std::string Player::getName() const {
	return *name;
}

int Player::getHighestRoll() const {
	return *this->getDice()->getHighestRoll();
}

Hand *Player::getHand() const {
	return handOfCards;
}

Dice *Player::getDice() const {
	return dice;
}

void Player::setNumDice(int numDice) {
	this->getDice()->setNumDice(numDice);
}

void Player::setIsTurn(bool value) {
	*this->isTurn = value;
}

bool Player::getIsTurn() const {
	return *this->isTurn;
}

int Player::getNumCountries() const {
	return this->countries.size();
}

//Returns a vector containing pointers to Country objects the player owns.
vector<Country *> Player::getCountries() const {
	return this->countries;
}

//Returns a sorted vector containing integers representing the keys of countries.
vector<int> Player::getCountryKeys() const {

	vector<int> keys;

	for (int i = 0; i < this->getNumCountries(); i++) {
		keys.push_back(this->getCountries()[i]->getCountryKey());
	}

	sort(keys.begin(), keys.end());

	return keys;

}


//Returns the name of the country with key k.
string getOwnerFromCountryKey(int k) {
	for (int i = 0; i< players.size(); i++) {
		for (int j = 0; j< players[i]->getNumCountries(); j++) {
			if (players[i]->getCountries()[j]->getCountryKey() == k) {
				return players[i]->getName();
			}
		}
	}
}

//=================
//END Getters and Setters
//=================



vector<int> Player::getAttackableCountries(Map *map) {

	int numCountries = this->getNumCountries();
	countries = this->getCountries();

	vector<int> neighbours;


	for (int i = 0; i< numCountries; i++) {
		for (int j = 0; j< this->getCountries()[i]->getNeighbourNum(); j++) {
			if (this->getCountries()[i]->getArmy() >= 2) {
				neighbours.push_back(this->getCountries()[i]->getNeighbours()[j]);
			}
		}
	}

	sort(neighbours.begin(), neighbours.end());

	vector<int>::iterator it;

	it = std::unique(neighbours.begin(), neighbours.begin() + (neighbours.size())); //Removing duplicate values.

	neighbours.resize(distance(neighbours.begin(), it));


	//Removing neighbours in which the player does not own.
	for (int j = 0; j < neighbours.size(); j++) {
		for (int i = 0; i < numCountries; i++) {
			if (neighbours[j] != this->getCountryKeys()[i]) {
				continue;
			}
			else {
				neighbours.erase(neighbours.begin() + j);
			}

		}
	}
	return neighbours;


}


//Assigns a country pointer to a player object.
void Player::addCountry(Country *country) {
	country->setOwner(this->getName());
	countries.push_back(country);
}

//Displays the names of countries the player owns.
void Player::displayCountries() {
	formatActionOutput(this->getName() + ": COUNTRIES");

	cout << this->getName() << " has " << this->getNumCountries() << " countries." << endl;

	for (int i = 0; i<this->countries.size(); i++) {
		cout << this->countries[i]->getName() << endl;
	}
}

//void Player::displayAttackableCountries() {
//    formatActionOutput(this->getName() + ": ATTACKABLE COUNTRIES");
//
//    for(int i = 0; i < this->countries.size(); i++) {
//        cout << "Attackable from " << this->countries[i]->getName() << ": ";
//        this->countries[i]->printNeighbours();
//    }
//}

int playerDriver() {
	std::string player1Name;
	std::string player2Name;
	int numDice;

	std::cout << "Enter player 1's name: " << std::endl;
	std::cin >> player1Name;

	std::cout << "Enter player 2's name: " << std::endl;
	std::cin >> player2Name;

	auto player1 = new Player(player1Name);
	auto player2 = new Player(player2Name);

	player1->RollDice();
	player2->RollDice();

	displayRoll(player1, player2);
	compareRolls(player1, player2);

	player1->showDiceFrequency();
	player2->showDiceFrequency();

	delete player1;
	delete player2;

	return 0;
}
