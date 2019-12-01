#pragma once
#include "Player.h"
#include "Map.h"
#include <vector>

class MainLoop;

//part2
class Game {

private:
	Map *gameMap;
	int *numberOfPlayer;
	
	vector<Player*> *playerArray;
	vector<Player*> *playerOrdered;
	int* armyNum;
	Country* countryArray;
	static void shuffle(vector<int>&array);
	static void shuffle(vector<Player*>*array);
public:
	Game();
	Game(Map &map, vector<Player*> playerArr);
	~Game();
	vector<Player*>* getPlayers() { return playerArray; };
	void startupTournament();
	void startupPhase();
	friend MainLoop;

};
//part 3
class MainLoop : public gameView {

private:
	bool* tourney;
	int* maxTurns;
	Game* startGame;
	vector<string>* winners; //we will know which game the player has won based on the index of the vector (i + 1)

    int checkIfEnd();
	void endDraw();


public:
	MainLoop();
	MainLoop(Game &game);
	~MainLoop();
	void startLoop(int turns);
	void statsDemo();

	//getters and setters

	void setTurns(int turn) { *maxTurns = turn; };
	void setTourney(bool tourny) { *tourney = tourny; };
	int getTurns() { return *maxTurns; };
	bool getTourney() { return *tourney; };
	vector<string>* getWinners() { return winners; };
};

void testPart2Part3();