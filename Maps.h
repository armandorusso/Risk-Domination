#pragma once
#include <iostream>
#include <string>
using namespace std;

//class definition for Country
class Country {
private:
	//data members
	string* name;                  
	int* countryKey;
	int* owner;                    
	int* neighbourNum; 
	int* neighbourArray;
	int* continentKey;

public:
	//definitions of constructors,destructor and functions
	Country();
	Country(string name, int countryK, int* neighbourA, int continentKey, int neighbourN, int own);
	~Country();
	string getName() { return *name; };
	int getCountryKey() { return *countryKey; };
	int* getNeighbours() { return neighbourArray; };
	int  getNeighbourNum();
	int getOwner() { return *owner; };
	int getContinentKey() { return *continentKey; };
	void setContinentKey(int key) { *continentKey = key; };
	void setCountryKey(int key) { *countryKey = key; };
	void setOwner(int key) { *owner = key; };
	void setName(string n) { *name = n; };
	void setNeighbourNum(int x) { *neighbourNum = x; };

};

//class definition of Continent object
class Continent {
private:
	//data members
	string* name;
	bool* conquered;
	int* owner;
	int* continentKey;
	int* countryNum; //total amount of countries the continent has

	//constructors and member functions
public:
	Continent();
	Continent(int key, string name, int num);
	~Continent();
	string getContinentName() { return *name; };
	void setContinentName(string n) { *name = n; };
	bool getConquered() { return *conquered; };
	void setConquered(bool conq) { *conquered = conq; };
	int getOwner() { return *owner; };
	void setOwner(int own) { *owner =own; };
	void setCountryNum(int count) { *countryNum = count; };
	int getCountryNum() { return *countryNum; };
	int getContinentKey() { return *continentKey; };
	void setContinetKey(int key) { *continentKey = key; };
};


//class definition for map object
class Map {

private:
	//data memebers
	int* countryCount;
	int* continentCount;
	int** matrix;
	Continent* array1;
	Country* array2;
	//private method
	void check(int i, int* arr);

public:

	//constructors and memeber functions
	Map();

	Map(Continent* array1, int size1, Country* array2, int size2);

	~Map();

	void checkMap();

	void setMatrix();

	void removeNeighbors(Country* country1, Country* country2) { std::cout << "this method remove neighbors"; };

	bool checkNeighbors(Country country1, Country country2);

	void printMatrix();

	//mutators
	int getCountryCount() { return *countryCount; };

	void setCountryCount(int count) { *countryCount = count; };

	int getContinentCount() { return *continentCount; };

	void setContinentCount(int count) { *continentCount = count; };

};
