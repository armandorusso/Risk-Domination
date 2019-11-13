#pragma once
#include<vector>
#include<string>
#include"Player.h"
#include "GameObservers.h"

using namespace std;

Observer::Observer() {

}

Observer::~Observer() {

}

//default constructor
 gameObserver::gameObserver() {
	
	
	player = NULL;
	phase = NULL;
	armyOwned = NULL;
	countriesOwned = NULL;
	continentOwned = NULL;
	subjects = NULL;
}
 //constructor taking vector of players
 gameObserver::gameObserver(vector<gameView*> players) {

	//all variables are properly initialized after update
	player = NULL;
	phase = new string();
	armyOwned = new int();
	countriesOwned = NULL;
	continentOwned = NULL;
	subjects = &players;

	//attaching this observer to all players in the vector
	for (int i = 0; i < subjects->size(); i++) {
	   subjects->at(i)->attach(this);
	}
 }

 //destructor
gameObserver::~gameObserver() {
  
	for (int i = 0; i < subjects->size(); i++) {
		subjects->at(i)->dettach(this);
	}
	delete phase;
	delete armyOwned;
	player = NULL;
	continentOwned = NULL;
	countriesOwned = NULL;
}

void gameObserver::Update(Player* player, string phase) {

	//assign player information to data members(updating)
	*this->phase = phase;
	*armyOwned = player->getTotalArmy();
	countriesOwned = player->getCountriesObjects();
	continentOwned = &player->getContinents();
	this->player = player;//game->getPlayerArray()->at(currentplayer);
	
	//displays updated information
	display();

}

void gameObserver::display() {
	
	system("CLS"); //clears previous phase information
	//diplays new phase information
	cout << "--------------------Observer----------------------" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "       Phase: " << player->getName() << " is " << *phase << endl;
	cout << "--------------------------------------------------" << endl;
    
	if (countriesOwned == NULL || player ==NULL || continentOwned==NULL) {
			cout << "Not Updated" <<endl;
			exit(0);
	}
	
	
	//if current phase is fortifying
	if (*phase == "Fortifying") {
		
		cout << "Countries Owned:" << endl;
		for (int i = 0; i < countriesOwned->size(); i++) {
			cout <<"Country: "<< countriesOwned->at(i)->getCountryKey()<< " ,Army value: " << countriesOwned->at(i)->getArmy() << endl;
		}
	   
	}
	//shows updated values after fortifying
	if (*phase == "Finished Fortifying") {
		cout << "New army values after fortifying: " << endl;

		for (int i = 0; i < countriesOwned->size(); i++) {
			cout << "Country: " << countriesOwned->at(i)->getCountryKey() << " ,Army value: " << countriesOwned->at(i)->getArmy()<<endl;
		}
	}
    //display for phase attacking
	if (*phase == "Attacking" || *phase=="Finished Attacking") {

		cout << "Number of Country Owned: " << player->getNumOfCountries() << endl;
		cout << "Number of Continent Conquered: " << player->getNumberContinent() << endl;
		cout << "Total Number of Armies: " << player->getTotalArmy() << endl;
		cout << "Armies on owned Countries:" << endl;
		
		for (int i = 0; i < countriesOwned->size(); i++) {
			cout << "Country: " << countriesOwned->at(i)->getCountryKey() << " ,Army value: " << countriesOwned->at(i)->getArmy() << endl;
		}	
	}

	//display for phase reinforcing
	if (*phase == "Reinforcing" || *phase == "Finished Reinforcing") {
		cout << "Armies on Country Owned:" << endl;
		for (int i = 0; i < countriesOwned->size(); i++) {
			cout << "Country: " << countriesOwned->at(i)->getCountryKey() << " ,Army value: " << countriesOwned->at(i)->getArmy() << endl;
		}


	}
	

}

//constructor
gameView::gameView(){

	obs = new list<Observer*>;
}

gameView::~gameView(){

	delete obs;
}


void gameView::attach(Observer* obs) {

	this->obs->push_back(obs);

}

void gameView::dettach(Observer* obs) {

	this->obs->remove(obs);
}

void gameView::notify(Player* player, string phase) {

	list<Observer*>::iterator i = obs->begin();
	for (; i != obs->end(); ++i)
		(*i)->Update(player, phase);

}