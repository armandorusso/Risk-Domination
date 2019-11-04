#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"
#include "Cards.h"
#include"Map.h"
#ifndef INC_345PROJECT_PLAYER_H
#define INC_345PROJECT_PLAYER_H

class Player {

private:
	std::string* name;
	Dice* dice;
	Hand* handOfCards;
	vector<int> *countriesKey;
	int* numberOfCountries;
	Map map;

public:
	Player(std::string name, Map &map);
	~Player();

	void reinforce();
	void attack();
	void fortify();
	void RollDice();
	void setNumDice(int numDice);
	void addCountry(int key);
	void removeCountry(int key);
	string getName() const;
	vector<int> getCountries() { return *countriesKey; };
	int getNumOfCountries() { return *numberOfCountries; };
	void setNumOfCountries(int num) { *numberOfCountries = num; };
	Dice* getDice() const;
	Hand* getHand() const;
	bool checkIfOwnCont();

};

#endif //INC_345PROJECT_PLAYER_H