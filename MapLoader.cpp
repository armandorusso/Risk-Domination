#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> //for exit function
#include <vector>
#include <regex>
#include <sstream>
#include "MapLoader.h"


using namespace std;

//constructors and destructors
FetchMap::FetchMap() {
	continentName = new string();
	armyValue = new int(0);
	color = new string();
	countryNum = new int(0);
	countryName = new string();
	continentNum = new int(0); //what continent it belongs to
	x = new int(0); //x and y arent going to be used, but i defined them so that i can store it into variables without having issues
	y = new int(0);
	countryKey = new int(0); //country number
	countryNeighbour = new int(0); //the neighbour country
}

FetchMap::~FetchMap() {

	delete continentName, armyValue, color, countryNum, continentNum, x, y, countryKey, countryNeighbour;
	continentName, armyValue, color, countryNum, continentNum, x, y, countryKey, countryNeighbour = NULL;
}

dummyMaps::dummyMaps() {
	continentArr = new vector<Continent*>;
	countryArr = new vector<Country*>;
}

dummyMaps::dummyMaps(vector<Continent*> continent, vector <Country*> country) {
	continentArr = new vector<Continent*>;
	countryArr = new vector<Country*>;

	int sizeCont = continent.size();
	int sizeCount = country.size();

	for (int i = 0; i < sizeCont; i++) {
		continentArr->push_back(continent.at(i));
	}
	for (int i = 0; i < sizeCount; i++) {
		countryArr->push_back(country.at(i));
	}
}

//copy constructor

dummyMaps::dummyMaps(const dummyMaps& map) {

	continentArr = new vector<Continent*>;
	countryArr = new vector<Country*>;

	for (int i = 0; i < map.continentArr->size(); i++) {
		continentArr->push_back(map.continentArr->at(i));
	}

	for (int i = 0; i < map.countryArr->size(); i++) {
		countryArr->push_back(map.countryArr->at(i));
	}

}

dummyMaps::~dummyMaps() {
	delete[] continentArr;
	continentArr = NULL;

	delete[] countryArr;
	countryArr = NULL;
}

dummyCountry::dummyCountry() {
	countryNam = new string();
	countryNum = new int();
	continentNum = new int();

}

dummyCountry::dummyCountry(string name, int countryN, int continentN) {
	countryNam = new string(name);
	countryNum = new int(countryN);
	continentNum = new int(continentN);


}

//copy constructor for country

dummyCountry::dummyCountry(const dummyCountry& cont) {
	countryNum = new int(cont.getCountryNum());
	countryNam = new string(cont.getCountryName());
	continentNum = new int(cont.getContinentNum());

}

dummyCountry::~dummyCountry() {
	delete countryNam, countryNum, continentNum;
	countryNam, countryNum, continentNum = NULL;

}

dummyContinent::dummyContinent() {
	continentName = new string();
	armyValue = new int();
	color = new string();
}

dummyContinent::dummyContinent(string continentN, int armyVal, int contiNum, string colour) {
	continentName = new string(continentN);
	armyValue = new int(armyVal);
	continentNumber = new int(contiNum);
	color = new string(colour);
}

dummyContinent::dummyContinent(const dummyContinent& cont) {

	continentName = new string(cont.getContinentName());
	armyValue = new int(cont.getArmyValue());
	continentNumber = new int(cont.getContValue());
	color = new string(cont.getColor());

}

dummyContinent::~dummyContinent() {
	delete continentName, armyValue, color;
	continentName, armyValue, color = NULL;
}


Map* FetchMap::getFileData(string fileName) {
	ifstream readMap;
	readMap.open(fileName);
	vector<Continent*> continentArr;
	vector<Country*> countryArr;
	int position = 0;


	if (readMap.fail()) { //if the file fails to open for some reason, exit the program
		cout << "Failed to open, please enter another file name ";
		return NULL;

	}
	string word;

	FetchMap obj;
	vector<dummyCountry*> allCountries;

	while (readMap >> word) {


		//reading and initializing the continents

		if (word == "[continents]") { //essentially, we fetch the data and store it into arrays of its type. Then, we initialize the Map


			int i = 0;
			while (readMap >> word && word != "[countries]" && readMap >> *obj.armyValue >> *obj.color) {


				i++; //for the continentNumber
				if (obj.continentName == NULL || (*obj.armyValue <= 0 || obj.armyValue == NULL)) {
					cout << "This is not the correct file format. Stopped at \"continents\". Please try another file";
					readMap.close();
					exit(1);
				}

				try {

					Continent* continent = new Continent(i, *obj.continentName, *obj.armyValue);
					continentArr.push_back(continent);

				}

				catch (exception e) {
					cout << e.what();
				}

			}

		}


		//reading and initializing countries

		if (word == "[countries]") {
			FetchMap obj2;
			int i = 0;
			while (readMap >> word && word != "[borders]" && readMap >> *obj2.countryName >> *obj2.continentNum >> *obj2.x >> *obj2.y) {

				*obj2.countryNum = stoi(word);
				*obj2.countryNum -= 1;


				if (*obj2.countryNum < 0 || obj2.countryName == NULL || *obj2.continentNum < 0 || *obj2.x < 0 || *obj2.y < 0) {
					cout << "This is not the correct file format. Stopped at \"countries\". Please try another file";
					readMap.close();
					return NULL;
				}
				//since we can only know the neighbours after reading the countries,
				//we will not make a neighbour array. Once we get to "borders",
				//we will initiliaze this array using a method

				dummyCountry* country = new dummyCountry(*obj2.countryName, *obj2.countryNum, *obj2.continentNum);
				allCountries.push_back(country);


			}

		}


		//reading and initiliazing neighbours

		if (word == "[borders]") {
			FetchMap obj3;
			string line;
			string dummyLine;
			readMap.get();


			while (getline(readMap, line, '\n')) {


				string theInts;
				int countryValue = 1;
				vector<int> neighbourArr;
				stringstream stream(line);

				while (!(stream.eof()) && stream >> theInts) {


					if (position == 0) {
						countryValue = stoi(theInts);
						position++;


					}

					else if (position == 1) {
						int oneNeigh = stoi(theInts);
						neighbourArr.push_back((oneNeigh - 1));

					}

				}

					Country* country = new Country(allCountries.at((countryValue - 1))->getCountryName(), allCountries.at((countryValue - 1))->getCountryNum(), neighbourArr, allCountries.at((countryValue - 1))->getContinentNum(), neighbourArr.size());
					countryArr.push_back(country);
					position = 0;


			}

		}


	}

	readMap.close();

	cout << "The file has been read succesfully!" << endl;
	//once all the data is read, time to initialize the map


	Map *completeMap = new Map(countryArr, continentArr);
	completeMap->setMatrix();
	completeMap->printMatrix();
	completeMap->checkMap();


	return completeMap;
}


