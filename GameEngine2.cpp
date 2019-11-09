#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex>
#include "GameEngine2.h"
#include "MapLoader.h"
#include "Cards.h"

using namespace std;

Loader::Loader(){

	map = NULL;
	players = new vector<Player*>;
	
}

Loader::~Loader() {
	delete map;
	delete players;
}



void Loader::menu() {
	int playerCount;
	string choice;
	FetchMap opener;
	

	cout << "Welcome!\nPlease enter the map file name you wish to load: " << endl;
	
	cin >> choice;
	Map *map1 = opener.getFileData(choice);
	while (map1 == NULL) {
		cin >> choice;
		map1 = opener.getFileData(choice);
	}

	cout << "Creating the Map..." << endl;

	map1->setMatrix();

	if (map1->checkMap() == false) {
		cout << "Invalid Map. Try again. Exiting program.";
		exit(0);
	}

    map = map1;
	map1 = NULL;


	//creating x amount of players
	while (true) {
		cout << "Enter a number of players (max is 6, minimum is 2) ";
		cin >> playerCount;
		if (playerCount < 1) {
			cout << "Enter a player count that's greater than 2 please. Enter another number " << endl;
		}

		else if (playerCount > 2 && playerCount <= 6) {
			break;
		}
	}

	
	for (int i = 0; i < playerCount; i++) {
		string name;
		cout << "What is the name of player " << (i + 1) << "? " << endl;
		cin >> name;
		Player* newPlayer = new Player(name, map);
		cout << "Name that you entered that is now in the Player object: " << newPlayer->getName() << endl;
		players->push_back(newPlayer);
	}

	cout << "Now hand of cards are being made: " << endl;

	Deck *deck = new Deck(map->getCountryCount());

	cout << "Everything is made! You're all good to go on playing! Enjoy playing! :)" << endl;
};

void testFunction() {

	Loader* engine = new Loader();

	engine->menu();

	delete engine;
}

