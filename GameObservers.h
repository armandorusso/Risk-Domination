
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
	virtual void notify(vector<Player*> *players, Map *map);
};
//observer super class
class Observer {
	                 
public:
	Observer();
    ~Observer();
    virtual void Update(Player* player , string phase) = 0;  
	//update has player and phase as parameter to know which player is making the notify call and where
	virtual void Update(vector<Player*> *players, Map *map) = 0;
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
	void Update(vector<Player*>* players, Map *map);    //overriden update method
	void display();


};

//derived class of observer
class statsObserver : public Observer {

private:
	//player information that get displayed
	vector<gameView*> *subjects;

public:
	statsObserver();
	statsObserver(vector<gameView*> players);     //Vector of player that the observer observes.
	~statsObserver();
	//Copy Constructor
	statsObserver(const statsObserver &s2);
	//Assignment operator
	statsObserver& operator=(const statsObserver &s2);
	void Update(vector<Player*> *players, Map *map);    //overriden update method
	void Update(Player* player, string phase);
	void display(vector<Player*>* players, Map *map);


};

