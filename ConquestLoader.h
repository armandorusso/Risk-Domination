#pragma once
#include "MapLoader.h" //includes the Map.h as well

//this class will be used as a class to temporarily store data
class Conquest {
//paramters

public:
	string* continentName; //what continent it belongs to
	string* countryName;
	vector<string>* stringNeighbours; //the neighbour country array


	//constructors
	Conquest();
	Conquest(string countName, string contName, vector<string> neighbours);
	Conquest(const Conquest& conq);
	~Conquest();

	//getters and setters
	string getContinentName() { return *continentName; };
	string getCountryName() { return *countryName; };
	vector<string> getCountryNeighbour() { return *stringNeighbours; };

	void setContinentName(string name) { *continentName = name; };
	//main map reader
	virtual Map* getConquestData(string fileName);
};

class ConquestMap {
protected:
	vector<Conquest*>* countries; //all the dummy countries
	vector<Continent*>* continents; //all actual continents
public:
	ConquestMap();
	ConquestMap(vector<Conquest*> count, vector<Continent*> cont);
	~ConquestMap();

	//getters and setters
	vector<Conquest*> getCountries() { return *countries; };
	vector<Continent*> getContinents() { return *continents; };
};
