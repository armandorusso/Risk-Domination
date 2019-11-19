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
	void menu();
	Map* getMap() { return map; };
	vector<Player*>* getPlayers() { return players; };

};

void testFunction();
