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

void Game::startupTournament() {

	//setting toatal army for each player
	for (int i = 0; i < playerArray->size(); i++) {

		playerArray->at(i)->addArmy(*armyNum);
	}

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

		(playerArray->at(i % (*numberOfPlayer)))->addCountry(CountryRandom.at(i));
		(CountryRandom.at(i))->setOwner(((playerArray->at(i % (*numberOfPlayer)))->getName()));
		(CountryRandom.at(i))->setOwnerObj(*playerArray->at(i % (*numberOfPlayer)));
	}
	//showing country assignment
	cout << endl;
	cout << "============== Showing country assignment =========================" << endl;

	for (int i = 0; i < *numberOfPlayer; i++) {
		cout << endl;
		vector<int>vect = playerArray->at(i)->getCountriesInts();
		int x = playerArray->at(i)->getNumOfCountries();

		cout << endl;
		cout << "Player " << playerArray->at(i)->getName() << " has Countries: " << endl;
		cout << endl;
		for (int i = 0; i < x; i++) {
			int y = vect.at(i);
			cout << y << "(" << (countryArray[y].getName()) << ")" << endl;
		}

	}

	for (int i = 0; i < playerArray->size(); i++) {

		playerArray->at(i)->setGame(this);
	}

	cout << endl;
	cout << "============== Starting Army Placement ==========================" << endl;
	//prompting user to assign army to countries
	for (int i = 0; i < *numberOfPlayer; i++) {
		bool valid = true;
		int army = *armyNum;
		vector<int> arr = playerArray->at(i)->getCountriesInts();
		int x = arr.size();
		cout << endl;
		cout << "Player " << (playerArray->at(i))->getName() << ":" << endl;
		cout << endl;
		int y;
		cout << "Placing armies" << endl;
		y = army / numOfCountry;

		for (int j = 0; j < x; j++) {
			
			army = army - y;

			countryArray[(arr.at(j))].addArmy(y);        //adding army to country

		}

	}
	//printing army placement and owner
	cout << endl;
	cout << "========================== Game Board ===============================" << endl;
	cout << endl;
	for (int i = 0; i < numOfCountry; i++) {

		cout << "Country" << i << " has owner: " << (countryArray[i].getOwner()) << ", Army: " << countryArray[i].getArmy() << endl;

	}
	cout << "Press any digit key to continue..." << endl;
	int x;
	cin >> x;

}



void Game::startupPhase() {

	//setting toatal army for each player
	for (int i = 0; i < playerArray->size(); i++) {

		playerArray->at(i)->addArmy(*armyNum);
	}

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

		(playerArray->at(i % (*numberOfPlayer)))->addCountry(CountryRandom.at(i));
		(CountryRandom.at(i))->setOwner(((playerArray->at(i % (*numberOfPlayer)))->getName()));
		(CountryRandom.at(i))->setOwnerObj(*playerArray->at(i % (*numberOfPlayer)));
	}
	//showing country assignment
	cout << endl;
	cout << "============== Showing country assignment =========================" << endl;

	for (int i = 0; i < *numberOfPlayer; i++) {
		cout << endl;
		vector<int>vect = playerArray->at(i)->getCountriesInts();
		int x = playerArray->at(i)->getNumOfCountries();

		cout << endl;
		cout << "Player " << playerArray->at(i)->getName() << " has Countries: " << endl;
		cout << endl;
		for (int i = 0; i < x; i++) {
			int y = vect.at(i);
			cout << y << "(" << (countryArray[y].getName()) << ")" << endl;
		}

	}

	for (int i = 0; i < playerArray->size(); i++) {
		
		playerArray->at(i)->setGame(this);
	}

	cout << endl;
	cout << "============== Starting Army Placement ==========================" << endl;
	//prompting user to assign army to countries
	for (int i = 0; i < *numberOfPlayer; i++) {
		bool valid = true;
		int army = *armyNum;
		vector<int> arr = playerArray->at(i)->getCountriesInts();
		int x = arr.size();
		cout << endl;
		cout << "Player " << (playerArray->at(i))->getName() << ":" << endl;
		cout << endl;
		for (int j = 0; j < x; j++) {
			int y;

			do {
				valid = true;
				cout << "How many armies you want to put in country " << arr.at(j) << "?" << "(" << army << ")" << endl;
				cin >> y;
				if (y > army || y < 0) {
					cout << "invalid amount of army" << endl;
					valid = false;
				}
			} while (!valid);

			army = army - y;
			countryArray[(arr.at(j))].addArmy(y);        //adding army to country

		}
	}
	//printing army placement and owner
	cout << endl;
	cout << "========================== Game Board ===============================" << endl;
	cout << endl;
	for (int i = 0; i < numOfCountry; i++) {

		cout << "Country" << i << " has owner: " << (countryArray[i].getOwner()) << ", Army: " << countryArray[i].getArmy() << endl;

	}
	int x;
	cin >> x;

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
	maxTurns = NULL;
	tourney = new bool(false);
	winners = new vector<string>;
}
//constructor
MainLoop::MainLoop(Game& game1) {

	startGame = &game1;  //has a link to game map
	maxTurns = new int();
	tourney = new bool(false);
	winners = new vector<string>;

}


//method to check if we have a game winner
int MainLoop::checkIfEnd() {

	int numOfCountry = (startGame->gameMap)->getCountryCount();
	int numOfPlayers = *(startGame->numberOfPlayer);
	vector<Player*>* arr = startGame->playerArray;


	for (int i = 0; i < numOfPlayers; i++) {
		if (((arr->at(i))->getNumOfCountries()) == numOfCountry) {         //wins if the number of country owned==country in continent
			//Notify observer that there is a winner
			notify(startGame->playerArray, startGame->gameMap);
			cout << arr->at(i)->getName() << " wins the game!" << endl;
			winners->push_back(arr->at(i)->getName()); //push the name of the winner

			if (!getTourney()) {
				exit(0);
			}

			else {
				cout << "We will move onto the next game!" << endl;

				for (int j = 0; j < 10; j++) {
					cout << endl;
				}

			}
			return 1; //1 means someone won
		}

	}
}


void MainLoop::endDraw() { //method is called if the number of turns in tourney mode exceeds the max amount of turns set
	cout << "It's a draw! There is no winner!\n\n\n\n" << endl;
	winners->push_back("Draw-No Winner");
	int numOfPlayers = *(startGame->numberOfPlayer);
	vector<Player*>* arr = startGame->playerArray;
	for (int i = 0; i < numOfPlayers; i++) {
		notify(startGame->playerArray, startGame->gameMap);
	}
}

//main game loop
void MainLoop::startLoop(int turns) {

	cout << endl;
	cout << "================ Starting Game phases ==================== " << endl;
	cout << endl;
	int numOfCountry = (startGame->gameMap)->getCountryCount();
	int numOfPlayers = *(startGame->numberOfPlayer);
	vector<Player*>* arr = startGame->playerArray;

	int counter = 0;
	int i = 0;
	int winner = 0;
	setTurns(turns);
	while (counter != turns) {  //infinite loop if its normal mode

		for (int j = 0; j < numOfPlayers; j++) {

			(arr->at(j))->executeReinforce();
			//Display statistics after reinforce
			notify(startGame->playerArray, startGame->gameMap);
//			(arr->at(j))->executeAttack();
			//Update player progress after attacking
//			notify(startGame->playerArray, startGame->gameMap);
			(arr->at(j))->executeFortify();
			//Display statistics after fortify
			notify(startGame->playerArray, startGame->gameMap);

			//testing checkIfEnd method (assuming player 0 wins at iteration 10)
			if (i == 9 && j == 0) {
				//set its number of country own to max and test if checkIfEnd works
				(arr->at(j))->setNumOfCountries(numOfCountry);

			}

			winner = checkIfEnd();
			if (winner == 1) {
				return;
			}

		}
		i = i + 1;
		counter++;
	}
	if(counter == turns)
	endDraw();
}



MainLoop::~MainLoop() {
	startGame = NULL;
}


void statsDemo() {
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
	Map *map2 = new Map(continentArray, 2, varrayCountry, 5);
	map2->setMatrix();

	Player* p1 = new Player("Bojan", map2);
	Player* p2 = new Player("Loser", map2);

	p1->addCountry(vc0);
	p1->addCountry(vc1);
	p1->addCountry(vc2);
	p1->addCountry(vc3);
	p2->addCountry(vc4);

	//vector of players
	vector<Player*> playerArr;

	playerArr.push_back(p1);
	playerArr.push_back(p2);

	vector<Player*>* playerArray = new vector<Player*>(playerArr);

	Game game1(*map2, playerArr);
	MainLoop loop1(game1);

	vector<gameView*>* vectPlayer = new vector<gameView*>;
	vectPlayer->push_back(&loop1);
	statsObserver* obs = new statsObserver(*vectPlayer);
	
	std::cout << "Calling notify after startup phase" << std::endl;

	loop1.notify(playerArray, map2);

	std::cout << "Calling notify after a player has won" << std::endl;

	p2->removeCountry(vc4->getCountryKey());
	p1->addCountry(vc4);

	loop1.notify(playerArray, map2);




}
/*
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
*/
//testStrategyAttack();
    //Run statsObserver demo
//	statsDemo();
//return 0;
//}
