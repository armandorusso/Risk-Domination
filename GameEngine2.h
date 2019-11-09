#pragma once
#include <iostream>
#include "Map.h"
#include "Dice.h"
#include "Player.h"
#include "Cards.h"

using namespace std;


class Loader {
	//data members
private:
	vector<Player*>* players;
	Map *map;

public:
	//constructors
	Loader();
	Loader(vector<Map*> maps, vector<Player*> player);
	~Loader();

	//functions
	vector<Player*> getPlayerArr() { return *players; };
	void menu();
};

void testFunction();
