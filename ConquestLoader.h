#pragma once
#include "MapLoader.h" //includes the Map.h as well

//this class will be used as a class to temporarily store data
class Conquest {
//parameters

protected:
	//variables
	string* continentName; //what continent it belongs to
	string* countryName;
	vector<string>* stringNeighbours; //the neighbour country array

	vector<Conquest*>* countries; //this is a dummy object. it will hold the data and the adapter will convert it to the approriate data we need for the Map
	vector<Continent*>* continents;
public:
	//constructors
	Conquest();
	Conquest(string countName, string contName, vector<string> neighbours);
	Conquest(const Conquest& conq);
	~Conquest();

	//getters and setters
	string getContinentName() { return *continentName; };
	string getCountryName() { return *countryName; };
	vector<string>* getCountryNeighbour() { return stringNeighbours; };

	void setContinentName(string name) { *continentName = name; };
};

class ConquestMap {
protected:
	vector<Conquest*>* countries; //all the dummy countries
	vector<Continent*>* continents; //all actual continents
public:
	//constructors
	ConquestMap();
	ConquestMap(vector<Conquest*> count, vector<Continent*> cont);
	~ConquestMap();

	//file method
	virtual void getConquestData(string fileName);

	//getters and setters
	vector<Conquest*> getCountries() { return *countries; };
	vector<Continent*> getContinents() { return *continents; };
};
