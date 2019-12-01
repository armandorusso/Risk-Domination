#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"
using namespace std;

static vector<Player*> players; // Vector containing the players.

//Outputs a title tag wit the given message.
void formatActionOutput(string message) {
	cout << "==================================================" << endl;
	cout << "\t\t" << message << endl;
	cout << "==================================================" << endl;
}

//Prints the contents of a vector of integers.
void printVector(vector<int> vector) {

	if (vector.size() != 0) {

		for (int i = 0; i < vector.size(); i++) {
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
	this->countries = new vector<Country*>();
	this->handOfCards = new Hand();
	countriesKey = new vector<int>();
	numberOfCountries = new int();
	map = NULL;
	continentOwned = new vector<Continent*>;
	numberOfContinent = new int(0);
	totalArmy = new int(0);
	game = NULL;
}

Player::Player(std::string name, Map& map) {
	this->name = new string(name);
	this->dice = new Dice();
	this->isTurn = new bool(false);
	this->countries = new vector<Country*>;
	this->handOfCards = new Hand();
	countriesKey = new vector<int>();
	this->map = &map;
	this->handOfCards = new Hand();
	numberOfCountries = new int(0);
	continentOwned = new vector<Continent*>;
	numberOfContinent = new int(0);
	totalArmy = new int(0);
	game = NULL;
}
Player::Player(string name, Map& map, Strategy* strategy) {

	this->name = new string(name);
	this->dice = new Dice();
	this->isTurn = new bool(false);
	this->countries = new vector<Country*>;
	this->handOfCards = new Hand();
	countriesKey = new vector<int>();
	this->map = &map;
	this->handOfCards = new Hand();
	numberOfCountries = new int(0);
	continentOwned = new vector<Continent*>;
	numberOfContinent = new int(0);
	totalArmy = new int(0);
	game = NULL;
	this->strategy = strategy;

}


Player::Player(std::string name, Map* map) {
    this->name = new string(name);
    this->dice = new Dice();
    this->isTurn = new bool(false);
    this->countries = new vector<Country*>;
    this->handOfCards = new Hand();
    countriesKey = new vector<int>();
    this->map = map;
    this->handOfCards = new Hand();
    numberOfCountries = new int(0);
	continentOwned = new vector<Continent*>;
	numberOfContinent = new int(0);
	totalArmy = new int(0);
	strategy = NULL;
	game = NULL;
}



Player::Player(std::string name) {
	this->name = new string(name);
	this->dice = new Dice();
	this->isTurn = new bool(false);
	this->countries = new vector<Country*>();
	this->numberOfCountries = new int(0);
	this->handOfCards = new Hand();
	countriesKey = new vector<int>();
	map = NULL;
	continentOwned = new vector<Continent*>;
	numberOfContinent = new int(0);
	totalArmy = new int(0);
	game = NULL;
}

Player::Player(const Player &r) {
    this->dice = new Dice(*r.getDice());
    this->isTurn = new bool(r.getIsTurn());

    this->countries = new vector<Country*>();

    if(r.countries->size()!= 0) {
        for(int i = 0; i<r.countries->size(); i++) {
            this->countries->push_back(r.countries->at(i));
        }
    }

    this->map = NULL;

    this->numberOfCountries = new int(*r.numberOfCountries);
    this->handOfCards = new Hand(*r.getHand());
    this->totalArmy = new int(*r.totalArmy);
    this->numberOfContinent = new int(*r.numberOfContinent);

    this->countriesKey = new vector<int>();

    if(r.countriesKey->size() != 0) {
        for(int i = 0; i< r.countriesKey->size(); i++) {
            countriesKey->push_back(r.countriesKey->at(i));
        }
    }

    continentOwned = new vector<Continent*>;

    if(r.continentOwned->size() != 0) {
        for(int i = 0; i< r.continentOwned->size(); i++) {
            continentOwned->push_back(r.continentOwned->at(i));
        }
    }

	
}



//Destructor for Player Class.


//DO WE WANT TO DELETE THE MAP IN THIS DESTRUCTOR? ans: No since its a refernce, will be deleted in map destructor
Player::~Player() {
	delete this->dice;
	delete this->name;
	delete this->isTurn;
	this->isTurn = nullptr;
	this->dice = nullptr;
	this->name = nullptr;
	delete[] countriesKey;
	delete handOfCards;
	handOfCards = nullptr;

	delete[] continentOwned;
	delete totalArmy;
	delete numberOfContinent;

	for (int i = 0; i < (*countries).size(); i++) {
		delete countries->at(i);
		countries->at(i) = nullptr;
	}

	countries->clear();

	strategy = nullptr;
}


//This method takes in a country key representing either an attacking or defending country.
//If the country is an attacker, it can only roll 1-3 dice, the max being the amount of armies on the country - 1.
//If the country is a defender, it can only roll 1-2 dice, the max being the amount of armies on the country.
//This method calls the Roll() method of the Player's Dice Object.
void Player::RollDice(int countryKey) {
	
	Country* arr = map->getCountryArray();
	
	int numDice = 0;
	Country* country = &arr[countryKey];

	int diceMax = country->getArmy() - 1;

	if (this->getIsTurn()) {
		if (diceMax >= 3) {
			cout << "Enter between 1 and 3 dice: ";
			cin >> numDice;
			setNumDice(numDice);
		}
		else {
			cout << "Enter between 1 and " << diceMax << " dice";
			cin >> numDice;
			setNumDice(numDice);
		}
	}
	else {
		diceMax += 1;
		if (diceMax >= 2) {
			cout << "Enter between 1 and 2 dice: ";
			cin >> numDice;
			setNumDice(numDice);
		}
		else {
			setNumDice(1);
		}
	}

	this->getDice()->Roll();
}

//This method takes in a country key representing either an attacking or defending country.
//If the country is an attacker, it can only roll 1-3 dice, the max being the amount of armies on the country - 1.
//If the country is a defender, it can only roll 1-2 dice, the max being the amount of armies on the country.
//This method calls the Roll() method of the Player's Dice Object.
void Player::RollDice(int countryKey, int randomNum) {
    int numDice = 0;
	Country* arr = map->getCountryArray();
	Country* country = &arr[countryKey];

    int diceMax = country->getArmy() - 1;

    if (this->getIsTurn()) {
        if (diceMax >= 3) {
            setNumDice(3);
        }
        else {
            setNumDice(diceMax);
        }
    }
    else {
        diceMax += 1;
        if (diceMax >= 2) {
            setNumDice(2);
        }
        else {
            setNumDice(1);
        }
    }

    this->getDice()->Roll();
}

//This method prints the rolls of each player object side by side.
//It also displays the highest roll of each player in the given turn.

void displayRoll(Player& player1, Player& player2) {

	vector<int>* player1CurrentRoll = player1.getDice()->getCurrentRoll();
	vector<int>* player2CurrentRoll = player2.getDice()->getCurrentRoll();

	std::cout << "====================" << std::endl;
	std::cout << "Rolling the dice" << std::endl;
	std::cout << "====================" << std::endl;

	std::cout << player1.getName() << "'s roll:";

	player1.getDice()->displayRolls(*player1CurrentRoll);

	std::cout << player2.getName() << "'s roll:";
	player2.getDice()->displayRolls(*player2CurrentRoll);
	std::cout << std::endl;

	std::cout << player1.getName() << "'s highest roll: " << player1.getHighestRoll() << std::endl;
	std::cout << player2.getName() << "'s highest roll: " << player2.getHighestRoll() << std::endl;

	std::cout << std::endl;
}



// =====================
//  PLAYER DICE METHODS
// =====================


//Returns true if Player1's highest roll is greater than Player 2's roll. False otherwise.
bool compareRolls(Player* player1, Player* player2) {

	std::cout << "====================" << std::endl;
	std::cout << "RESULT" << std::endl;
	std::cout << "====================" << std::endl;
	if (player1->getHighestRoll() <= player2->getHighestRoll()) {
		std::cout << player1->getName() << " loses an army.\n" << std::endl;
		return false;
	}
	else {
		std::cout << player2->getName() << " loses an army.\n" << std::endl;
		return true;
	}
}


//Shows how many times each value was rolled.
void Player::showDiceFrequency() {

	std::cout << "====================" << std::endl;
	std::cout << this->getName() << ": DICE FREQUENCY" << std::endl;
	std::cout << "====================" << std::endl;
	this->getDice()->printFrequency();
}

//Shows the percentage of each dice roll.
void Player::showDiceValuePercentage() {
	std::cout << "====================" << std::endl;
	std::cout << "DICE Percentage" << std::endl;
	std::cout << "====================" << std::endl;
	this->getDice()->displayPercentage();
}




void Player::attackDemo() {
	cout << *name <<" is attacking..." << endl;

}

void Player::fortifyDemo() {
	cout << *name <<" is fortifying..." << endl;

}

void Player::reinforceDemo() {
	cout << *name <<" is reinforcing..." << endl;

}

//=================================================
// attack, fortify,reinforce using current strategy
//=================================================

void Player::attackUsingStrategy() {

	strategy->executeAttack(this);

}


void Player::fortifyUsingStrategy() {

	strategy->executeFortify(this);

}
void Player::reinforceUsingStrategy() {

	strategy->executeReinforce(this);

}

// ==========================================
//      REINFORCE ATTACK FORTIFY( Human )
// ==========================================
void Player::fortify() {

	notify(this, "Fortifying");  //notify observer at start of reinforece



	std::cout << std::endl;

	string ans1;
	int ans2, ans3;
	bool valid;
	Country* arrayCountry = (*map).getCountryArray();

	//showing countries owned
	cout << "You have the following countries: " << endl;
	for (int i = 0; i < *numberOfCountries; i++) {
		cout << countriesKey->at(i) << endl;
	}

	cout << "Do you want to fortify a Country? " << endl;
	cin >> ans1;

	if (ans1 == "yes") {      //continue if yes, else stop


		cout << "which country you want to fortify?" << endl;

		do {
			cin >> ans2;

			valid = false;
			//loops untill input is correct
			for (int i = 0; i < *numberOfCountries; i++) {
				if (countriesKey->at(i) == ans2) {
					valid = true;
				}
			}
			if (valid == false) {
				cout << "Invalid input, try again: " << endl;
			}


		} while (!valid);

		//show amount of armies in countries owned
		cout << "You have " << arrayCountry[ans2].getArmy() << " armies in country " << ans2 << endl;
		cout << "From which country you want to move army? " << endl;

		do {
			cin >> ans3;

			valid = false;

			for (int i = 0; i < *numberOfCountries; i++) {

				int key = countriesKey->at(i);
				//loop if input not valid
				if (key == ans3 && key!=ans2 && (arrayCountry[key].getOwner() == *(this->name))) {
					valid = true;
				}
			}
			if (valid == false) {
				cout << "Invalid input(You do not own this country), try again: " << endl;
			}

		} while (!valid);

		int armyvalue = arrayCountry[ans3].getArmy();
		cout << "You have " << armyvalue << " armies in country " << ans3 << endl;
		cout << "How many Armies do you want to move?" << endl;

		int ans4;

		do {
			cin >> ans4;

			valid = false;
			//moving the armies, not valid if input exceeds number of armies
			if (ans4 < armyvalue) {
				valid = true;
				arrayCountry[ans3].subtractArmy(ans4);
				arrayCountry[ans2].addArmy(ans4);
				arrayCountry[ans3].getOwnerObj()->subtractArmy(ans4);
				arrayCountry[ans2].getOwnerObj()->addArmy(ans4);
			}
			else {
				cout << "Invalid input(You dont have enough army, try agian:)" << endl;
			}
		} while (valid == false);

		cout << "Country" << ans2 << " now has " << arrayCountry[ans2].getArmy() << " armies." << endl;
		cout << "Country" << ans3 << " now has  " << arrayCountry[ans3].getArmy() << " armies." << endl;

		arrayCountry = NULL;
	}

	notify(this, "Finished Fortifying"); //show change after fortify

}
void Player::reinforce() {

	notify(this, "Reinforcing");

	int armiesToExchange = 0;

	//GET ARMIES FOR COUNTRIES
	armiesToExchange = this->getNumCountries() / 3;

	//Must get minimum 3 armies
	if (armiesToExchange < 3) {
		armiesToExchange = 3;
	}

	//GET ARMIES FROM CONTINENT-CONTROL VALUE
	armiesToExchange = armiesToExchange + this->checkIfOwnCont();

	//EXCHANGE CARDS FOR ARMIES
	while (this->getHand()->exchange()) {
		armiesToExchange = armiesToExchange + *this->getHand()->getNumArmies();
	}

	//Human Player

	//Distribute all armies
	while (armiesToExchange != 0) {

		//Display the number of armies to distribute and a list of owned countries
		std::cout << std::endl << "You have " << armiesToExchange << " armies left to distribute." << std::endl;
		std::cout << "Here are the countries you own:" << std::endl;

		for (int i = 0; i < this->getCountriesObjects()->size(); i++) {
			std::cout << "Country key: " << this->getCountriesObjects()->at(i)->getCountryKey() << ", Armies: " << this->getCountriesObjects()->at(i)->getArmy() << std::endl;
		}

		//Get the country the player wants to reinforce
		int chosenKey = 0;
		std::cout << "Which country do you want to reinforce?" << std::endl;
		std::cin >> chosenKey;

		//Check if the player owns the chosen country key
		bool validKey = false;
		do {
			for (int i = 0; i < this->getCountriesObjects()->size(); i++) {
				if (this->getCountriesObjects()->at(i)->getCountryKey() == chosenKey) {
					validKey = true;
				}
			}

			if (!validKey) {
				std::cout << "Please enter a valid country key." << std::endl;
				std::cin >> chosenKey;
			}
		} while (!validKey);

		//Get the number of armies the player wants to distribute to the chosen country
		int chosenArmies = 0;
		std::cout << "You have " << armiesToExchange << " armies left to distribute." << std::endl;
		std::cout << "How many armies do you want to distribute?" << std::endl;
		std::cin >> chosenArmies;

		//Validate number of armies input
		while (chosenArmies > armiesToExchange || chosenArmies < 1) {
			std::cout << "Please enter a valid number of armies" << std::endl;
			std::cin >> chosenArmies;
		}

		//Distribute the armies in the chosen country
		for (int i = 0; i < this->getCountriesObjects()->size(); i++) {
			if (this->getCountriesObjects()->at(i)->getCountryKey() == chosenKey) {
				this->getCountriesObjects()->at(i)->addArmy(chosenArmies);
			}
		}

		//Display how many countries were distributed to which country
		std::cout << "Distributed " << chosenArmies << " armies to country " << chosenKey << std::endl;

		//Reduce the number of armies left to exchange
		armiesToExchange = armiesToExchange - chosenArmies;
	}

	notify(this, "Finished Reinforcing");
}


void Player::attack() {
	notify(this, "Attacking"); //notify observer to show initial state

	this->setIsTurn(true);

	formatActionOutput(this->getName() + ": ATTACK PHASE");

	string answer;
	int attackingCountry; // key for the attacking country
	int defendingCountry; // key for the defending country

	vector<int> attackableCountries = this->getAttackableCountries(this->map);

	Country* arrayCountry = (*map).getCountryArray();
	vector<Player*>* arrPlayer = game->getPlayers();

	do {
		answer = "";

		cout << "=========================" << endl;
		cout << "Countries you own" << endl;
		cout << "=========================" << endl;

		printVector(this->getCountryKeys());

		cout << "=========================" << endl;
		cout << "Countries you can attack" << endl;
		cout << "=========================" << endl;

		printVector(attackableCountries);

		cout << endl;

		cout << "Do you wish to attack? (y for yes, anything else for no)" << endl;
		cin >> answer;

		if (answer != "y") {
			break;
		}

		bool found = false;

		//This loop continues if one enters a value within their list of owned countries.
		do {
			cout << "Which country do you want to attack? " << endl;

			cin >> defendingCountry;

			vector<int>::iterator it = std::find(attackableCountries.begin(), attackableCountries.end(), defendingCountry);

			if (it != attackableCountries.end()) {
				found = true;
			}
			else {
				cout << "Invalid Number" << endl;
				continue;
			}

		} while (!found);

		found = false;

		//This loop continues if one enters a country in which they do not own.
		do {
			cout << "Which country do you want to attack with? " << endl;

			vector<int> attackingCountryKeys;

			for (int i = 0; i < this->getCountryKeys().size(); i++) {
				attackingCountryKeys.push_back(this->getCountryKeys()[i]);
			}

			cin >> attackingCountry;


			vector<int>::iterator it = std::find(attackingCountryKeys.begin(), attackingCountryKeys.end(), attackingCountry);

			if (it != attackingCountryKeys.end()) {
				found = true;
			}
			else {
				cout << "You can't attack with " << attackingCountry << endl;
				cout << "You don't own it!" << endl;
				continue;
			}
		} while (!found);


		//If attacking and defending countries are not neighbours, display appropriate message, and continue to the next iteration of the loop.
		if (!this->map->checkNeighbors(attackingCountry, defendingCountry)) {
			cout << "You can't attack " << defendingCountry << " with " << attackingCountry << endl;
			cout << "They are not neighbours" << endl;
			continue;
		}

		printArmiesFromCountries(&arrayCountry[attackingCountry],&arrayCountry[defendingCountry]);

		cout << attackingCountry << endl;

		if (arrayCountry[attackingCountry].getArmy() < 2) {     //vector out of bounce here for country 1
			cout << "You can't attack " << defendingCountry << " with " << attackingCountry << endl;
			cout << "You don't have enough armies on this country." << endl;
			continue;
		}





		//Attacking conditions are met.
		cout << "Attacking " << defendingCountry << " with " << attackingCountry << endl << endl;

		Player* defendingPlayer = arrayCountry[defendingCountry].getOwnerObj();
		Player* attackingPlayer = arrayCountry[attackingCountry].getOwnerObj();

		//Time to roll the dice for the attacking and defending player.
		this->RollDice(attackingCountry);

		defendingPlayer->RollDice(defendingCountry);


		// Displays the rolls of each player.
		::displayRoll(*attackingPlayer, *defendingPlayer);

		//If attacking player rolls greater than defending player, defending player loses army. Otherwise, attacking country loses army.
		if (::compareRolls(this, defendingPlayer)) {
			arrayCountry[defendingCountry].subtractArmy(1);
		}
		else {
			arrayCountry[attackingCountry].subtractArmy(1);
		}

		//If attacking results in 0 armies for the defending player, attacking player adds that country to their list of countries. Defending country is removed
		//from defending player.
		if (arrayCountry[defendingCountry].getArmy() == 0) {

			Country* dCountry = &arrayCountry[defendingCountry];
			Country* aCountry = &arrayCountry[attackingCountry];

			this->addCountry(dCountry);
			::removeCountry(dCountry, defendingPlayer);

			cout << "Country transferred to " << this->getName() << endl;

			//Attacker can transfer 0 to n-1 armies from their country to the country they just won.
			//If user inputs too many armies, appropriate message is displayed and loop is entered.
			if (aCountry->getArmy() > 1) {

				int inputArmies;
				int maxArmiesToTransfer = aCountry->getArmy() - 1;

				do {
					cout << "Choose between 0 and " << (aCountry->getArmy() - 1) << " armies to transfer to " << defendingCountry << ": ";
					cin >> inputArmies;
					if (inputArmies > maxArmiesToTransfer || inputArmies < 0) {
						cout << "Invalid number of armies." << endl;
					}
				} while (inputArmies > maxArmiesToTransfer || inputArmies < 0);

				//Transfer successful.
				cout << "Transfering " << inputArmies << " armies from " << attackingCountry << " to " << defendingCountry << ".\n" << endl;
				dCountry->addArmy(inputArmies);
				aCountry->subtractArmy(inputArmies);
			}
			else {
				cout << "You don't have enough armies to transfer. " << endl;
			}

			//Updating the attackableCountries vector.
			attackableCountries = this->getAttackableCountries(map);
		}

		printArmiesFromCountries(&arrayCountry[attackingCountry], &arrayCountry[defendingCountry]);

		//Clearing the currentRoll values in the dice objects, so that
		//more values are not pushed in.
		this->getDice()->getCurrentRoll()->clear();
		defendingPlayer->getDice()->getCurrentRoll()->clear();

	} while (answer == "y"); //END ATTACK LOOP

	formatActionOutput(this->getName() + ": ATTACK PHASE COMPLETE");

	notify(this, "Finished Attacking"); //notify observer to show change after attack.
}



//Returns pointer to owner of country with key k.
Player* getPlayerFromCountryKey(int k) {
	for (int i = 0; i < players.size(); i++) {
		for (int j = 0; j < players[i]->getCountryKeys().size(); j++) {
			if (players[i]->getCountryKeys()[j] != k) {
				continue;
			}
			return players[i];
		}
	}
}


void Player::addCountry(int key) {
	countriesKey->push_back(key);
	(*numberOfCountries)++;
}


//==============
// USE THIS ONE
//==============
//Assigns a country pointer to a player object and sets its owner to the name of that player object.
void Player::addCountry(Country* country) {
    country->setOwner(this->getName());
    countriesKey->push_back(country->getCountryKey());
    countries->push_back(country);
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


//Decrements army of Country with key k.
void loseArmy(int k) {
	
	Country* country = getCountryFromCountryKey(k);
	country->subtractArmy(1);
}

int Player::checkIfOwnCont() {

	Continent* arrayCont = map->getContinentArray();
	Country* arrayCountry = map->getCountryArray();
	int  x = map->getContinentCount();
	int armiesToAdd = 0;

	int* arr = new int[x];
	for (int i = 0; i < x; i++) {
		arr[i] = 0;
	}

	for (int i = 0; i < this->getNumCountries(); i++) {
		int key = this->getCountriesObjects()->at(i)->getCountryKey();
		int continentKey = arrayCountry[key].getContinentKey();

		arr[continentKey]++;

	}

	for (int i = 0; i < x; i++) {
		if (arr[i] == arrayCont[i].getCountryNum()) {
			if (i == 0) {
				armiesToAdd = armiesToAdd + 3;
			}
			if (i == 1) {
				armiesToAdd = armiesToAdd + 2;
			}
			arrayCont->setConquered(true);
			arrayCont[i].setOwner(*name);
		}
	}
	return armiesToAdd;
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

int Player::getHighestRoll() const {
	return *this->getDice()->getHighestRoll();
}

Dice* Player::getDice() const {
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
	return  *numberOfCountries;
}

//Returns a vector containing pointers to Country objects the player owns.
vector<Country*>* Player::getCountriesObjects() const {
	return this->countries;
}

//Returns a sorted vector containing integers representing the keys of countries.
vector<int> Player::getCountryKeys() const {

	vector<int> keys;

	for (int i = 0; i < this->getNumCountries(); i++) {
		keys.push_back(this->getCountriesObjects()->at(i)->getCountryKey());
	}

	sort(keys.begin(), keys.end());

	return keys;

}

//Returns the country with key k.
Country* getCountryFromCountryKey(int k) {

	
	
	for (int i = 0; i < players.size(); i++) {

		for (int j = 0; j < players[i]->getNumCountries(); j++) {

			if (players[i]->getCountriesObjects()->at(j)->getCountryKey() == k) {

				return players[i]->getCountriesObjects()->at(j);
			}
		}
	}
}

//Returns vector of attackable countries.
//An attackable country which is a neighbour to a country (with number of armies >= 2) of the attacking player.
vector<int> Player::getAttackableCountries(Map* map) {

	int numCountries = this->getNumCountries();
	countries = this->getCountriesObjects();

	vector<int> neighbours;

	for (int i = 0; i < numCountries; i++) {
		for (int j = 0; j < this->getCountriesObjects()->at(i)->getNeighbourNum(); j++) {
			if (this->getCountriesObjects()->at(i)->getArmy() >= 2) {
				neighbours.push_back(this->getCountriesObjects()->at(i)->getNeighbours()[j]);
			}
		}
	}

	sort(neighbours.begin(), neighbours.end());

	vector<int>::iterator it;

	//Removing duplicate values.
	it = std::unique(neighbours.begin(), neighbours.begin() + (neighbours.size()));

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

//=================
//END Getters and Setters
//=================


// ====================
//  COUNTRY METHODS
// ====================



//Removes country from list of countries that player owns.
void removeCountry(Country* country, Player* player) {
	vector<int> countryKeys = player->getCountryKeys();
	vector<int>::iterator it = find(countryKeys.begin(), countryKeys.end(), country->getCountryKey());

	int index = 0;
	for (int i = 0; i < countryKeys.size(); i++) {
		if (country->getCountryKey() == countryKeys[i]) {
			index = i;
		}
	}

	countryKeys.erase(countryKeys.begin() + index);
}

//Displays the names of countries the player owns.
void Player::displayCountries() {
	formatActionOutput(this->getName() + ": COUNTRIES");

	cout << this->getName() << " has " << this->getNumCountries() << " countries." << endl;

	for (int i = 0; i < this->countries->size(); i++) {
		cout << this->countries->at(i)->getName() << endl;
	}
}


void printArmiesFromCountries(Country* c1, Country* c2) {

	

	cout << "=========================" << endl;
	cout << "\tArmy Count" << endl;
	cout << "=========================" << endl;
	cout << "Attacking armies: ";
	cout << c1->getArmy() << endl;
	cout << "Defending armies: ";
	cout << c2->getArmy() << endl;

	cout << endl;
}

//Assignment Operator
const Player& Player::operator=(const Player& r) {
    if(&r != this) {
        delete dice;
        delete name;
        delete isTurn;
        delete [] countriesKey;
        delete handOfCards;
        delete map;

        for (int i = 0; i < (*countries).size(); i++) {
            delete countries->at(i);
            countries->at(i) = nullptr;
        }

        dice = new Dice(*r.dice);
        name = new string(*r.name);
        isTurn = new bool(*r.isTurn);

        //Need copy constructors for map, handOfCards

        for(int i = 0; i < countriesKey->size(); i++) {
            countriesKey[i] = r.countriesKey[i];
        }

    }

    return *this;
}

//DRIVERS
void attackDriver() {
	int numCountry = 5;
	int numContinent = 2;

	Continent* cont1 = new Continent();
	Continent* cont2 = new Continent();
	Continent* continentArray = new Continent[2];
	continentArray[0] = *cont1;
	continentArray[1] = *cont2;

	int varr0[3] = { 1,3,4 };
	int varr1[2] = { 2,3 };
	int varr2[2] = { 4,1 };
	int varr3[2] = { 0,2 };
	int varr4[2] = { 1,3 };

	Country* vc0 = new Country("c0", 0, varr0, 1, 3);       //name,key,array of neighbor key
	Country* vc1 = new Country("c1", 1, varr1, 1, 2);
	Country* vc2 = new Country("c2", 2, varr2, 1, 2);
	Country* vc3 = new Country("c3", 3, varr3, 2, 2);
	Country* vc4 = new Country("c4", 4, varr4, 2, 2);

	Country* varrayCountry = new Country[5];
	varrayCountry[0] = *vc0;
	varrayCountry[1] = *vc1;
	varrayCountry[2] = *vc2;
	varrayCountry[3] = *vc3;
	varrayCountry[4] = *vc4;

	Map* map2 = new Map(continentArray, 2, varrayCountry, 5);

	Player* player1 = new Player("Christopher", *map2, new HumanPlayer());
	Player* player2 = new Player("Peter", *map2);

	players.push_back(player1);
	players.push_back(player2);
    
	vc0->addArmy(5);
	vc1->addArmy(5);
	vc2->addArmy(5);
	vc3->addArmy(5);
	vc4->addArmy(5);
	
	//testing observer
	vector<gameView*>* vectPlayer = new vector<gameView*>;
	vectPlayer->push_back(player1);
	vectPlayer->push_back(player2);
	gameObserver* obs = new gameObserver(*vectPlayer);

	//Setting the adjacency matrix
	map2->setMatrix();

	player1->addCountry(vc0);
	player1->addCountry(vc1);
	player2->addCountry(vc2);
	player2->addCountry(vc3);
	player2->addCountry(vc4);

	

    for(int i = 0; i< player1->getCountriesObjects()->size(); i++) {
        player1->addArmy(player1->getCountriesObjects()->at(i)->getArmy());
    }

	player1->attackUsingStrategy();
}



void fortifyDriver()
{
	//creating array of countries
	int varr0[3] = { 1,2,3 };
	int varr1[3] = { 0,2,3 };
	int varr2[3] = { 2,4,1 };
	int varr3[2] = { 0,2 };
	int varr4[3] = { 1,3 };

	Country* vc0 = new Country("c0", 0, varr0, 1, 3);
	Country* vc1 = new Country("c1", 1, varr1, 1, 3);
	Country* vc2 = new Country("c2", 2, varr2, 1, 3);
	Country* vc3 = new Country("c3", 3, varr3, 2, 2);
	Country* vc4 = new Country("c4", 4, varr4, 2, 3);

	Country* varrayCountry = new Country[5];
	varrayCountry[0] = *vc0;
	varrayCountry[1] = *vc1;
	varrayCountry[2] = *vc2;
	varrayCountry[3] = *vc3;
	varrayCountry[4] = *vc4;
	Continent* cont1 = new Continent();
	Continent* cont2 = new Continent();
	Continent* continentArray = new Continent[2];
	continentArray[0] = *cont1;
	continentArray[1] = *cont2;

	//creating map
	Map *map2 = new Map(continentArray, 2, varrayCountry, 5);
	(*map2).setMatrix();

	Player* p1 = new Player("Jack", *map2);
	Player* p2 = new Player("James", *map2);
	Player* p3 = new Player("Eren", *map2);

	vector<gameView*>* vectPlayer = new vector<gameView*>;
	vectPlayer->push_back(p1);
	vectPlayer->push_back(p2);
	vectPlayer->push_back(p3);
	gameObserver* obs = new gameObserver(*vectPlayer);

	p1->addCountry(vc0);
    p1->addCountry(vc1);

    p1->addCountry(vc2);
    p2->addCountry(vc3);

	vc0->addArmy(5);
	vc1->addArmy(2);
	vc2->addArmy(2);
	vc3->addArmy(3);
	vc4->addArmy(3);

	p1->fortify();
}

//testing observer
void observerDriver() {

    char ans;
	reinforceDriver();
	cout << "continue?(y for yes)" << endl;
	cin >> ans;
	if (ans == 'y')
	fortifyDriver();
	cout << "continue?(y for yes)" << endl;
	cin >> ans;
	if (ans == 'y')
	attackDriver();

}

void testStrategy() {

	//creating array of countries
	int varr0[3] = { 1,2 };
	int varr1[3] = { 0,2,3 };
	int varr2[3] = { 2,4,1 };
	int varr3[2] = { 0,2 };
	int varr4[3] = { 1,3 };

	Country* vc0 = new Country("c0", 0, varr0, 1, 2);
	Country* vc1 = new Country("c1", 1, varr1, 2, 3);
	Country* vc2 = new Country("c2", 2, varr2, 1, 3);
	Country* vc3 = new Country("c3", 3, varr3, 2, 2);
	Country* vc4 = new Country("c4", 4, varr4, 2, 2);

	Country* varrayCountry = new Country[5];
	varrayCountry[0] = *vc0;
	varrayCountry[1] = *vc1;
	varrayCountry[2] = *vc2;
	varrayCountry[3] = *vc3;
	varrayCountry[4] = *vc4;
	Continent* cont1 = new Continent();
	Continent* cont2 = new Continent();
	Continent* continentArray = new Continent[2];
	continentArray[0] = *cont1;
	continentArray[1] = *cont2;

	//creating map
	Map* map2 = new Map(continentArray, 2, varrayCountry, 5);
	(*map2).setMatrix();

	//AggressivePlayer* str = new AggressivePlayer();
	//BenevolentPlayer* str2 = new BenevolentPlayer();
	RandomPlayer* str = new RandomPlayer();
	CheaterPlayer* str2 = new CheaterPlayer();

	Player* p1 = new Player("Jack", *map2, str2);
	Player* p2 = new Player("James", *map2, str);
	Player* p3 = new Player("Eren", *map2, str);

	vector<gameView*>* vectPlayer = new vector<gameView*>;
	vectPlayer->push_back(p1);
	vectPlayer->push_back(p2);
	vectPlayer->push_back(p3);
	gameObserver* obs = new gameObserver(*vectPlayer);

	p1->addCountry(vc0);
	p1->addCountry(vc1);

	p1->addCountry(vc2);
	p2->addCountry(vc3);
	p2->addCountry(vc4);

	vc0->addArmy(5);
	vc1->addArmy(2);
	vc2->addArmy(2);
	vc3->addArmy(3);
	vc4->addArmy(5);

	p1->fortifyUsingStrategy();//agressive fortify
	int x;
	cin >>x;
	p2->fortifyUsingStrategy();//benevolant fortify
}

void testStrategyAttack() {
    int numCountry = 5;
    int numContinent = 2;

    Continent* cont1 = new Continent();
    Continent* cont2 = new Continent();
    Continent* continentArray = new Continent[2];
    continentArray[0] = *cont1;
    continentArray[1] = *cont2;

    int varr0[3] = { 1,3,4 };
    int varr1[2] = { 2,3 };
    int varr2[2] = { 4,1 };
    int varr3[2] = { 0,2 };
    int varr4[2] = { 1,3 };

    Country* vc0 = new Country("c0", 0, varr0, 1, 3);       //name,key,array of neighbor key
    Country* vc1 = new Country("c1", 1, varr1, 1, 2);
    Country* vc2 = new Country("c2", 2, varr2, 1, 2);
    Country* vc3 = new Country("c3", 3, varr3, 2, 2);
    Country* vc4 = new Country("c4", 4, varr4, 2, 2);

    Country* varrayCountry = new Country[5];
    varrayCountry[0] = *vc0;
    varrayCountry[1] = *vc1;
    varrayCountry[2] = *vc2;
    varrayCountry[3] = *vc3;
    varrayCountry[4] = *vc4;

    
	CheaterPlayer* cheater = new CheaterPlayer();
	//AggressivePlayer* aggressiveAttack = new AggressivePlayer();
    BenevolentPlayer* benevolentAttack = new BenevolentPlayer();

    Map* map2 = new Map(continentArray, 2, varrayCountry, 5);

    Player* player1 = new Player("Christopher", *map2, cheater);
	Player* player2 = new Player("Peter", *map2, benevolentAttack);

    players.push_back(player1);
    players.push_back(player2);

    //testing observer
    vector<gameView*>* vectPlayer = new vector<gameView*>;
    vectPlayer->push_back(player1);
    vectPlayer->push_back(player2);
    gameObserver* obs = new gameObserver(*vectPlayer);

    //Setting the adjacency matrix
    map2->setMatrix();

    player1->addCountry(vc0);
    player1->addCountry(vc1);
    player2->addCountry(vc2);
    player2->addCountry(vc3);
    player2->addCountry(vc4);

	vc0->setOwnerObj(player1);
	vc1->setOwnerObj(player1);
	vc2->setOwnerObj(player2);
	vc3->setOwnerObj(player2);
	vc4->setOwnerObj(player2);

    vc0->addArmy(5);
    vc1->addArmy(5);
    vc2->addArmy(5);
    vc3->addArmy(5);
    vc4->addArmy(5);
    


    for(int i = 0; i< player1->getCountriesObjects()->size(); i++) {
            player1->addArmy(player1->getCountriesObjects()->at(i)->getArmy());
    }

    player1->attackUsingStrategy();

 //   player2->attackUsingStrategy();
}

int main(){
//    attackDriver();
//	fortifyDriver();
//	observerDriver();
//	testStrategy();

   testStrategyAttack();
//reinforceDriver();

}
