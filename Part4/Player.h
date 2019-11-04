//
// Created by Christopher Diktakis on 2019-10-26.
//
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
	Hand *handOfCards;
	vector<Country *> countries;

public:
	Player(std::string name);
	Player();
	~Player();

	void showDiceFrequency();
	void showDiceValuePercentage();
	void reinforce();
	void attack();
	void fortify();
	void RollDice();
	void displayRoll();
	void loseArmy();
	void setNumDice(int numDice);
	void decideNumDice();
	void setIsTurn(bool value);
	int getHighestRoll() const;
	bool getIsTurn() const;
	bool canAttack();
	bool isDefending();
	int getNumCountries() const;
	vector<Country *> getCountries() const;
	void addCountry(Country *country);
	Country *hasCountry(Country *country);
	bool hasCountry(Country *country) const;
	void attackCountry(Country &country);

	vector<int> getCountryKeys() const;

	void displayCountries();
	void displayAttackableCountries();

	vector<int> getAttackableCountries(Map *map);



	Dice *getDice() const;
	std::string getName() const;
	Hand *getHand() const;
	int playerDriver();
};

bool compareRolls(Player *player1, Player *player2);
void displayRoll(Player *player1, Player *player2);





