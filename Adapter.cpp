#include "Adapter.h"
#include "MapLoader.h"


	//we want the conquest to adapt to the original map loader. to do this, we create a conquest object
ConquestToOg::ConquestToOg() {
		mapLoad = new MapLoader();
}

Map* ConquestToOg::convertToOg() { //the adapter method (request)
	        
	
	vector<Country*>* actualCountry = new vector <Country*>;

	
			for (int i = 0; i < countries->size(); i++) {
				actualCountry->push_back(new Country()); //initializing the objects in each index
			}

			for (int i = 0; i < countries->size(); i++) {
				

				actualCountry->at(i)->setName(countries->at(i)->getCountryName()); //setting the country name of the actual countries
				//this is done by fetching each dummy country's names and setting it in the actual countries
	
				actualCountry->at(i)->setCountryKey(i); //setting them a country key
				//setting everything in the country with the data from the dummy object. the following loop will set the neighbour array

				actualCountry->at(i)->setContinentName(getCountries().at(i)->getContinentName()); //setting the continent name

				for (int j = 0; j < continents->size(); j++) { //setting the continent key. this is done by checking the continent name then setting the key
					if (continents->at(j)->getContinentName() == actualCountry->at(i)->getContinentName()) {
						actualCountry->at(i)->setContinentKey(j);
					}
				}

			}
			//the main issue with the conquest file format is that the neighbours are listed as strings (i.e, their country name)
			//this is why we are using the adapter, to convert these strings into readeable data (i.e, country keys as ints)

			//setting the neighbour array now. this is done by looping through all the countries, comparing the dummy objects country name with
			//the actual country name
			//if their country names are the same, push the country key into the neighbour array
			for (int i = 0; i < actualCountry->size(); i++) {
				
				vector<int> *neighborInt = new vector<int>;
				vector<string>* arrNeigh = countries->at(i)->getCountryNeighbour();
				
				for (int y = 0; y < arrNeigh->size(); y++) {

					for (int j = 0; j < countries->size(); j++) {

						if (arrNeigh->at(y) == countries->at(j)->getCountryName()) {
							neighborInt->push_back(j);
						}
					}
				}
				
				int size = neighborInt->size();
				int* arr = new int[size];
				for (int a = 0; a < size; a++) {
					arr[a] = neighborInt->at(a);
				}
				actualCountry->at(i)->setNeighbour(arr);
				actualCountry->at(i)->setNeighbourNum(size);

	
			}
			
			Map *map = mapLoad->returnMap(*continents, *actualCountry); //making the actual map

			return map;
}
