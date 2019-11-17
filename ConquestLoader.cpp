#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> //for exit function
#include <vector>
#include <sstream>
#include "ConquestLoader.h"

//constructors
Conquest::Conquest() {
	continentName = new string();
	countryName = new string();
	stringNeighbours = new vector<string>; //the neighbour country
}

Conquest::Conquest(string countName, string contName, vector<string> neighbours) {
	countryName = new string(countName);
	continentName = new string(contName);
	stringNeighbours = new vector<string>;

	for (int i = 0; i < neighbours.size(); i++) {
		stringNeighbours->push_back(neighbours.at(i));
	}
}

Conquest::Conquest(const Conquest& conq) {
	continentName = new string(*conq.continentName); 
	countryName = new string(*conq.countryName);
	stringNeighbours = new vector<string>; //the neighbour country

	for (int i = 0; i <conq.stringNeighbours->size(); i++) {
		stringNeighbours->push_back(conq.stringNeighbours->at(i));
	}
}


Conquest::~Conquest() {

	delete continentName, countryName, stringNeighbours;
	continentName = NULL, countryName = NULL, stringNeighbours = NULL;
}

//dummy map constructors
ConquestMap::ConquestMap() {
	countries = new vector<Conquest*>;
	continents = new vector<Continent*>;
}

ConquestMap::ConquestMap(vector<Conquest*> count, vector<Continent*> cont) {
	countries = new vector<Conquest*>;
	continents = new vector<Continent*>;

	for (int i = 0; i < count.size(); i++) {
		getCountries().push_back(count.at(i));
	}

	for (int i = 0; i < cont.size(); i++) {
		getContinents().push_back(cont.at(i));
	}
}


ConquestMap::~ConquestMap() {
	for (int i = 0; i < getContinents().size(); i++) {
		delete getContinents().at(i);
	}
	for (int i = 0; i < getCountries().size(); i++) {
		delete getCountries().at(i);
	}
	countries = NULL;
	continents = NULL;
}



Map* Conquest::getConquestData(string fileName) {

	Conquest tempData1;
	vector<Conquest*> countries; //this is a dummy object. it will hold the data and the adapter will convert it to the approriate data we need for the Map
	vector<Continent*> continents; 
	string pointer; //points to the location in the file

	ifstream mapStream(fileName);

	//if the file failed to open (i.e, couldnt find the file), return NULL indicating the map cannot be made
	if (mapStream.fail()) {
		cout << "Conquest Map failed to open. Please try something else";
		return NULL;
	}

	while (mapStream >> pointer) {

		//continent section
		
		if (pointer == "[Continents]" || pointer == "[continents]") { //initialize continents
			string sentence;
			int continentNumber = 0; //used to count the total amount of continents and index the continents
			
			while (getline(mapStream, pointer, '\n') && pointer != "[Territories]") { //if we read the end of the line, stop reading and parse the data
				stringstream lineStream(pointer);
				string word;
				string continentName; //name of the continent
				int counter = 0; //this is to let us know where we are in the sentence
				int armyValue = 0;
				continentNumber++;
				
				while (getline(lineStream, word, '=')) {
					
					if (counter == 0) {
						continentName = word;
						counter++;
					}

					else if (counter == 1) {
						armyValue = stoi(word);
					}
				}

				Continent* continent = new Continent(continentNumber, continentName, armyValue);
				continents.push_back(continent);
			}

		}

		if (pointer == "[Territories]" || pointer == "[territories]") {
			while (getline(mapStream, pointer, '\n')) { //if we read the end of the line, stop reading and parse the data
				stringstream lineStream(pointer);
				string word;
				string continentName; //name of the continent
				string continentItBelongs;
				int counter = 0; //this is to let us know where we are in the sentence
				vector<string> neighbours; //all the neighbours

				while (getline(lineStream, word, ',')) {
					if (counter == 0) {
						continentName = word;
						counter++;
					}

					else if (counter == 1 || counter == 2) {
						counter++;
						continue;
					}

					else if (counter == 3) {
						continentItBelongs = word;
						counter++;
					}

					else if (counter == 4) {
						neighbours.push_back(word);
					}
				}
				Conquest* country = new Conquest(continentName, continentItBelongs, neighbours);
			}


		}
	}

	ConquestMap dummyMap(countries, continents); //dummy map

	cout << "The Conquest file has been read fully!" << endl;
	//call the adapter method, which will convert all the data into data that is useable
}
