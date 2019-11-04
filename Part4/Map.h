#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//class definition for Country
class Country {
private:
	//data members
	string * name;
	int* countryKey;
	string* owner;
	int* neighbourNum;
	int* neighbourArray;
	int* continentKey;
	int* army;
public:
	//definitions of constructors,destructor and functions
	Country();
	Country(string name, int countryK, int* neighbourA, int continentKey, int neighbourN);
	~Country();
	string getName() { return *name; };
	int getCountryKey() { return *countryKey; };
	int* getNeighbours() { return neighbourArray; };
	int  getNeighbourNum();
	string getOwner() { return *owner; };
	int getContinentKey() { return *continentKey; };
	void setContinentKey(int key) { *continentKey = key; };
	void setCountryKey(int key) { *countryKey = key; };
	void setOwner(string name) { *owner = name; };
	void setName(string n) { *name = n; };
	void setNeighbourNum(int x) { *neighbourNum = x; };
	int getArmy() { return *army; };
	void addArmy(int x) { (*army) += x; };
	void subtractArmy(int x) { *army -= x; };




	vector<int> getAttackableNeighbours();
	bool isAttackable();
	void printNeighbours();
};

//class definition of Continent object
class Continent {
private:
	//data members
	string * name;
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
	void setOwner(int own) { *owner = own; };
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
	Country* array2;   //array of all countries in map(key of country==index)
					   //private method
	void check(int i, int* arr);

public:

	//constructors and memeber functions
	Map();

	Map(Continent* array1, int size1, Country* array2, int size2);

	~Map();

	bool checkMap();

	void setMatrix();

	void removeNeighbors(Country* country1, Country* country2) { std::cout << "this method remove neighbors"; };

	bool checkNeighbors(int c1, int c2);

	void printMatrix();

	//mutators
	int getCountryCount() { return *countryCount; };

	void setCountryCount(int count) { *countryCount = count; };

	int getContinentCount() { return *continentCount; };

	void setContinentCount(int count) { *continentCount = count; };

	Country* getCountryArray() { return array2; };
};





