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
	void startupPhase();
	friend MainLoop;

};
//part 3
class MainLoop : public gameView {

private:
	Game* startGame;
    void checkIfEnd();

public:
	MainLoop();
	MainLoop(Game &game);
	~MainLoop();
	void startLoop();


};

void testPart2Part3();