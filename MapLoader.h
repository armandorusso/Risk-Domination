#pragma once

#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class dummyCountry {

private:
	string* countryNam;
	int* countryNum; //the country but in ordered number form
	int* continentNum; //what continent number its from
	

public:
	dummyCountry();
	dummyCountry(string name, int countryN, int continentNum);
	dummyCountry(const dummyCountry& cont);
	~dummyCountry();

	//getters and setters
	int getCountryNum() const { return *countryNum; };
	string getCountryName() const { return *countryNam; };
	int getContinentNum() const { return *continentNum; };


};

class dummyContinent {

private:
	string* continentName;
	int* armyValue;
	int* continentNumber;
	string* color;

public:
	dummyContinent();
	dummyContinent(string continentN, int armyVal, int contiNum, string colour);
	dummyContinent(const dummyContinent& cont);
	~dummyContinent();

	//getters and setters
	string getContinentName() const { return *continentName; };
	int getArmyValue() const { return *armyValue; };
	int getContValue() const { return *continentNumber; };
	string getColor() const { return *color; };

	void setContinentName(string contName) { *continentName = contName; };
	void setArmyValue(int army) { *armyValue = army; };
	void setContValue(int contiNum) { *continentNumber = contiNum; };
	void setColor(string col) { *color = col; };


};

class dummyMaps {

private:
	vector<Continent*>* continentArr;
	vector<Country*>* countryArr;

public:
	dummyMaps();
	dummyMaps(vector<Continent*> continentA, vector<Country*> countryA);
	dummyMaps(const dummyMaps& map);
	~dummyMaps();



	void printMap();

};

class FetchMap {

public:
	string* continentName;
	int* armyValue;
	string* color;
	int* countryNum; //country number (that way we can refer to the countries easier)
	string* countryName;
	int* continentNum; //what continent it belongs to
	int* x; //x and y arent going to be used, but i defined them so that i can store it into variables without having issues
	int* y;
	int* countryKey; //country number
	int* countryNeighbour; //the neighbour country



	FetchMap(); //for the constructor, let the parameter be a file name and open the stream in the constructor
	~FetchMap();

	//getters and setters
	string getContinentName() { return *continentName; };
	int getArmyValue() { return *armyValue; };
	string getColor() { return *continentName; };
	int getCountryNum() { return *countryNum; };
	string getCountryName() { return *countryName; };
	int getContinentNum() { return *continentNum; };
	int getX() { return *x; };
	int getY() { return *y; };
	int getCountryKey() { return *countryKey; };
	int getCountryNeighbour() { return *countryNeighbour; };

	void setContinentName(string name) { *continentName = name; };

	//methods
	Map* getFileData(string fileName); //reads the file and initializes the objects
};



