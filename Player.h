
#pragma once

#include <iostream>
#include <vector>
#include "Dice.h"
#include "Map.h"
#include "Cards.h"

class Player {
private:
	std::string* name;
	Dice* dice;
	bool* isTurn;
	Hand* handOfCards;
	vector<Country*>* countries;
	Map* map;
	vector<int>* countriesKey;
	int* numberOfCountries;

public:
	Player(std::string name, Map* map);
	Player(std::string name, Map& map);
	Player(std::string name);
	Player();
	~Player();

	vector<int> getCountriesInts() { return *countriesKey; };
	int getNumOfCountries() { return *numberOfCountries; };
	void setNumOfCountries(int num) { *numberOfCountries = num; };
	Hand* getHand() const;
	int checkIfOwnCont();

	void showDiceFrequency();
	void showDiceValuePercentage();
	void fortify();
	void reinforce();
	void attack();
	void RollDice(int key);
	void setNumDice(int numDice);

	void setIsTurn(bool value);
	int getHighestRoll() const;
	bool getIsTurn() const;
	void removeCountry(int key);
	int getNumCountries() const;
	vector<Country*>* getCountriesObjects() const;
	void addCountry(Country* country);
	void addCountry(int key);
	bool hasCountry(Country* country) const;
	void setHand();

	vector<int> getCountryKeys() const;

	void displayCountries();

	vector<int> getAttackableCountries(Map* map);


	void reinforceDemo();
	void attackDemo();
	void fortifyDemo();

	Dice* getDice() const;
	std::string getName() const;
};

//Returns true if player1
bool compareRolls(Player* player1, Player* player2);
void displayRoll(Player& player1, Player& player2);

Player* getPlayerFromCountryKey(int k);
Country* getCountryFromCountryKey(int k);

//Remove country from player object.
void removeCountry(Country* country, Player* player);

void loseArmy(int k);

void printArmiesFromCountries(int c1, int c2);

int reinforceDriver();
void attackDriver();
void fortifyDriver();