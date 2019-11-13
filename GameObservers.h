
#pragma once
#include<stdlib.h>
#include<vector>
#include<list>

//foward declaration
class Player;
class Observer ;

//subject 
class gameView {
private:

	list <Observer*> *obs;   //list of observers

public:
   
	gameView();
	~gameView();
	
	virtual void attach(Observer* ob);
	virtual void dettach(Observer* ob);
	virtual void notify(Player* player, string currentPhase);
};
//observer super class
class Observer {
	                 
public:
	Observer();
    ~Observer();
    virtual void Update(Player* player , string phase) = 0;  
	//update has player and phase as parameter to know which player is making the notify call and where
};

//derived class of observer
class gameObserver : public Observer {

private:
	
	//player information that get displayed
	vector<gameView*> *subjects;
	Player* player;
	string* phase;
	int *armyOwned;
	vector<Country*>* countriesOwned;
	vector<Continent*>* continentOwned;

public:
	
	gameObserver();
	gameObserver(vector<gameView*> players);     //Vector of player that the observer observes.
	~gameObserver();
	void Update(Player* player,string phase);    //overriden update method
	void display();


};

