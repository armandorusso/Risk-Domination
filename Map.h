#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Player.h>
using namespace std;

//class definition for Country
class Country {
private:
    //data members
    string* name;
    int* countryKey;
    string* owner;
    int* neighbourNum;
    int* neighbourArray;
    int* continentKey;
    int* army;
	string* continentName;
	Player* ownerObj;

public:
    //definitions of constructors,destructor and functions
    Country();
	//Country(const Country& copy);
	//const Country& operator=(const Country& assign);
    Country(string name, int countryK, int* neighbourA, int continentKey, int neighbourN);
    Country(string name, int countryK, vector<int> neighbourA, int continentKey, int neighbourN);
    ~Country();
    string getName() const { return *name; };
    int getCountryKey() const { return *countryKey; };
    int* getNeighbours() const { return neighbourArray; };
    int  getNeighbourNum() const;
    string getOwner() const { return *owner; };
    int getContinentKey() const { return *continentKey; };
    void setContinentKey(int key) { *continentKey = key; };
    void setCountryKey(int key) { *countryKey = key; };
    void setOwner(string name) { *owner = name; };
    void setName(string n) { *name = n; };
    void setNeighbourNum(int x) { *neighbourNum = x; };
    int getArmy() const { return *army; };
    void addArmy(int x) { (*army) += x; };
    void subtractArmy(int x) { *army -= x; };
	void setNeighbour(int* arr) { neighbourArray = arr; };
	void setContinentName(string name) { *continentName = name; };
	string getContinentName() { return *continentName; };
	Player* getOwnerObj() { return ownerObj; };
	void setOwnerObj(Player pla) { ownerObj = &pla; };
};

//class definition of Continent object
class Continent {
private:
    //data members
    string* name;
    bool* conquered;
    string* owner;
    int* continentKey;
    int* countryNum; //total amount of countries the continent has

    //constructors and member functions
public:
    Continent();
	Continent(const Continent& copy);
	const Continent& operator=(const Continent& assign);
    Continent(int key, string name, int num);
    ~Continent();
    string getContinentName() const{ return *name; };
    void setContinentName(string n) { *name = n; };
    bool getConquered() const { return *conquered; };
    void setConquered(bool conq) { *conquered = conq; };
    string getOwner() const { return *owner; };
    void setOwner(string own) { *owner = own; };
    void setCountryNum(int count) { *countryNum = count; };
    int getCountryNum() const { return *countryNum; };
    int getContinentKey() const { return *continentKey; };
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
	//Map(const Map& copy);
	//const Map& operator=(const Map& assign);
    Map(vector<Country*> count, vector<Continent*> cont);
    Map(Continent* array1, int size1, Country* array2, int size2);
    ~Map();

    bool checkMap();

    void setMatrix();

    void removeNeighbors(Country* country1, Country* country2) { std::cout << "this method remove neighbors"; };

    bool checkNeighbors(Country country1, Country country2);

    bool checkNeighbors(int c1, int c2);

    void printMatrix();

    //mutators
    int getCountryCount() const { return *countryCount; };

    void setCountryCount(int count) { *countryCount = count; };

    int getContinentCount() const { return *continentCount; };

    void setContinentCount(int count) { *continentCount = count; };

    Country* getCountryArray() const { return array2; };

    Continent* getContinentArray() const { return array1; };

	int** getMatrix() const { return matrix; };
};







