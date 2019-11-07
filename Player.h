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
    Map *map;
    vector<int> *countriesKey;

    int* numberOfCountries;


public:
    Player(std::string name, Map *map);
    Player(std::string name, Map &map);
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
    void reinforce();
    void attack();
    void RollDice(int key);
    void displayRoll();
    void setNumDice(int numDice);
    void decideNumDice();
    void setIsTurn(bool value);
    int getHighestRoll() const;
    bool getIsTurn() const;
    bool canAttack();
    void removeCountry(int key);
    bool isDefending();
    int getNumCountries() const;
    vector<Country *> getCountriesObjects() const;
    void addCountry(Country *country);
    void addCountry(int key);
    Country *hasCountry(Country *country);
    bool hasCountry(Country *country) const;
    void attackCountry(Country &country);

    void setHand() {

    }

    vector<int> getCountryKeys() const;

    void displayCountries();
    void displayAttackableCountries();

    vector<int> getAttackableCountries(Map *map);


    void reinforceDemo();
    void attackDemo();
    void fortifyDemo();

    Dice *getDice() const;
    std::string getName() const;
    int playerDriver();
};

bool compareRolls(Player *player1, Player *player2);
void displayRoll(Player &player1 , Player &player2);
Player *getPlayerFromCountryKey(int k);
Country *getCountryFromCountryKey(int k);
void removeCountry(Country *country, Player *player);

void loseArmy(int k);

int printArmiesFromCountries(int c1, int c2);

int reinforceDriver();
void attackDriver();
int fortifyDemo();






