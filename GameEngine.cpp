#include<vector>
#include"GameEngine.h"
#include<iostream>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;

//default constructor
Game::Game() {
	gameMap = NULL;
	numberOfPlayer = NULL;
	playerArray = NULL;
	playerOrdered = NULL;
	armyNum = NULL;
	countryArray = NULL;
}

//constructor
Game::Game(Map& map, vector<Player*> playerArr) {

	gameMap = &map;   //link to game map
	countryArray = gameMap->getCountryArray();
	numberOfPlayer = new int(playerArr.size());
	playerArray = new vector<Player*>(playerArr);

	//calculating number of armies
	switch (*numberOfPlayer) {
	case(2):armyNum = new int(40);
		break;
	case(3):armyNum = new int(35);
		break;
	case(4):armyNum = new int(30);
		break;
	case(5):armyNum = new int(25);
		break;
	case(6):armyNum = new int(20);
		break;
	default: cout << "Number of player is not valid";
		exit(0);
	}

	shuffle(playerArray);



}

void Game::startupPhase() {


	//getting array of countries from map
	int numOfCountry = gameMap->getCountryCount();

	//an array of shuffled countries to assign randomly to players
	vector<Country*> CountryRandom;

	vector<int> arr;
	for (int j = 0; j < numOfCountry; ++j)
		arr.push_back(j);

	shuffle(arr);

	for (int i = 0; i < numOfCountry; i++) {
		int x = arr.back();
		arr.pop_back();

		CountryRandom.push_back(&(countryArray[x]));

	}


	//assigning countries to players


	for (int i = 0; i < numOfCountry; i++) {

		(playerArray->at(i % (*numberOfPlayer)))->addCountry((CountryRandom.at(i))->getCountryKey());
		(CountryRandom.at(i))->setOwner(((playerArray->at(i % (*numberOfPlayer)))->getName()));
	}
	//showing country assignment
	for (int i = 0; i < *numberOfPlayer; i++) {
		vector<int>vect = playerArray->at(i)->getCountriesInts();
		int x = playerArray->at(i)->getNumOfCountries();
		cout << "Player " << playerArray->at(i)->getName() << " has Countries: " << endl;

		for (int i = 0; i < x; i++) {
			int y = vect.at(i);
			cout << y << "(" << (countryArray[y].getName()) << ")" << endl;
		}

	}
	//prompting user to assign army to countries
	for (int i = 0; i < *numberOfPlayer; i++) {

		int army = *armyNum;
		vector<int> arr = playerArray->at(i)->getCountriesInts();
		int x = arr.size();

		cout << "Player " << (playerArray->at(i))->getName() << ":" << endl;

		for (int j = 0; j < x; j++) {
			int y;
			cout << "How many armies you want to put in country " << arr.at(j) << "?" << "(" << army << ")" << endl;
			cin >> y;
			if (y > army || y < 0) {
				cout << "invalid amount of army" << endl;
				exit(0);
			}
			army = army - y;
			countryArray[(arr.at(j))].addArmy(y);        //adding army to country

		}
	}
	//printing army placement and owner
	cout << "Game Board:" << endl;
	for (int i = 0; i < numOfCountry; i++) {

		cout << "Country" << i << " has owner: " << (countryArray[i].getOwner()) << ", Army: " << countryArray[i].getArmy() << endl;

	}
}

void Game::shuffle(vector<int>& array) {

	std::default_random_engine engine;
	engine.seed(time(0));
	auto rng = engine;
	std::shuffle(std::begin(array), std::end(array), rng);
}
void Game::shuffle(vector<Player*>* array) {

	std::default_random_engine engine;
	engine.seed(time(0));
	auto rng = engine;
	std::shuffle(std::begin(*array), std::end(*array), rng);
}

//destructors
Game::~Game() {


	delete numberOfPlayer;
	delete[] playerArray;
	delete armyNum;
	gameMap = NULL;
	numberOfPlayer = NULL;
	playerArray = NULL;
	playerOrdered = NULL;
	armyNum = NULL;
}
//default constructor
MainLoop::MainLoop() {

	startGame = NULL;
}
//constructor
MainLoop::MainLoop(Game& game1) {

	startGame = &game1;  //has a link to game map

}

//method to check if we have a game winner
void MainLoop::checkIfEnd() {

	int numOfCountry = (startGame->gameMap)->getCountryCount();
	int numOfPlayers = *(startGame->numberOfPlayer);
	vector<Player*>* arr = startGame->playerArray;


	for (int i = 0; i < numOfPlayers; i++) {
		if (((arr->at(i))->getNumOfCountries()) == numOfCountry) {         //wins if the number of country owned==country in continent

			//Notify observer that there is a winner
			notify(startGame->playerArray, startGame->gameMap);
			exit(0);
		}

	}
}

//main game loop
void MainLoop::startLoop() {

	int numOfCountry = (startGame->gameMap)->getCountryCount();
	int numOfPlayers = *(startGame->numberOfPlayer);
	vector<Player*>* arr = startGame->playerArray;

	int i = 0;
	while (true) {  //infinite loop

		for (int j = 0; j < numOfPlayers; j++) {

			(arr->at(j))->reinforceDemo();
			//Display statistics after reinforce
			notify(startGame->playerArray, startGame->gameMap);
			(arr->at(j))->attackDemo();
			//Update player progress after attacking
			notify(startGame->playerArray, startGame->gameMap);
			(arr->at(j))->fortifyDemo();
			//Display statistics after fortify
			notify(startGame->playerArray, startGame->gameMap);

			//testing checkIfEnd method (assuming player 0 wins at iteration 10)
			if (i == 9 && j == 0) {
				//set its number of country own to max and test if checkIfEnd works
				(arr->at(j))->setNumOfCountries(numOfCountry);

			}

			checkIfEnd();

		}
		i = i + 1;
	}
}
MainLoop::~MainLoop() {
	startGame = NULL;
}


int main() {

	//creating array of countries
	int varr0[3] = { 1,3,4 };
	int varr1[3] = { 1,3,5 };
	int varr2[3] = { 2,4,1 };
	int varr3[2] = { 0,2 };
	int varr4[3] = { 1,3,5 };

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
	Map map2(continentArray, 2, varrayCountry, 5);
	map2.setMatrix();

	Player* p1 = new Player("Jack", map2);
	Player* p2 = new Player("James", map2);
	Player* p3 = new Player("Eren", map2);


	//vector of players
	vector<Player*> playerArr;

	playerArr.push_back(p1);
	playerArr.push_back(p2);
	playerArr.push_back(p3);

	Game game1(map2, playerArr);
	MainLoop loop1(game1);

	vector<gameView*>* vectPlayer = new vector<gameView*>;
	vectPlayer->push_back(&loop1);
	statsObserver* obs = new statsObserver(*vectPlayer);

	game1.startupPhase();

	loop1.startLoop();
	cout << "ends";

}
