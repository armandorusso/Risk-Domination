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

//selects the approriate maps for normal and tounrey mode
void Loader::selectMap() {
	string choice;
	MapLoader opener;
	Map* map1;
	
		cout << "Please enter the map file name you wish to load : " << endl;

		cin >> choice; //check if its a maploader or a conquest maploader
	    map1 = opener.getFileData(choice);
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
}

void Loader::selectMap2(string choice) {

	MapLoader opener;
	Map* map1;

	map1 = opener.getFileData(choice);
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
}





int Loader::menu() {
	int playerCount;
	string choice;
	string mode;
	MapLoader opener;


	cout << "*********=============*************Welcome to Risk, the boardgame!*************=============*********\n====================================================================================================\nBefore we begin, which mode would you like to chose?" << endl;

	while (true) {
		cout << "Please enter a number for the choice:\n" << endl;
		cout << "===============================\n\tMode Selection\n===============================\n1.Normal Mode : Just regular Risk!\n2.Tournament Mode : A tourney style gameplay!" << endl;

		cin >> mode;

		int numberMode = stoi(mode);

		if (numberMode == NULL || (numberMode < 0 && numberMode >= 3)) {
			continue;
		}

		else if (numberMode == 1) {
			break;
		}

		else if(numberMode == 2){
			//call tournament menu
			return 2;
		}

	}

	cout << "Option 1 selected: Normal Mode!\nPlease enter the map file name you wish to load: " << endl;
	
	selectMap();

	//creating x amount of players
	while (true) {
		cout << "Enter a number of players (max is 6, minimum is 2) ";
		cin >> playerCount;
		if (playerCount <= 1) {
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

	//create the deck
	cout << "Now hand of cards are being made: " << endl;

	Deck *deck = new Deck(map->getCountryCount());

	cout << "Everything is made! You're all good to go on playing! Enjoy playing! :)\n\n\n\n\n" << endl;
	return 1;
};

void testFunction() {

	Loader* engine = new Loader();

	engine->menu();

	delete engine;
}

