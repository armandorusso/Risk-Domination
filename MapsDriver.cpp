#include <iostream>
#include"Maps.h"

using namespace std;

int main()
{
	int numCountry = 5;
	int numContinent = 2;
	cout << "Case1: Not Valid Map" << endl;
	int arr0[3] = { 1,3,4 };
	int arr1[3] = { 1,3,5 };
	int arr2[3] = { 2,4,1 };
	int arr3[1] = { 0 };
	int arr4[3] = { 3,5 };
	//creating country objects
	//parameters: name,key,array of neighbor key,continent key,array of neighbor size,owner id.
	Country* c0 = new Country("0", 0, arr0, 1, 3, 1);
	Country* c1 = new Country("c1", 1, arr1, 1, 3, 2);
	Country* c2 = new Country("c2", 2, arr2, 1, 3, 3);
	Country* c3 = new Country("c3", 3, arr3, 2, 1, 4);
	Country* c4 = new Country("c4", 4, arr4, 2, 3, 5);
	//creating array of country objects
	Country* arrayCountry = new Country[5];
	arrayCountry[0] = *c0;
	arrayCountry[1] = *c1;
	arrayCountry[2] = *c2;
	arrayCountry[3] = *c3;
	arrayCountry[4] = *c4;

	Continent* cont1 = new Continent();
	Continent* cont2 = new Continent();
	Continent* continentArray[2] = { cont1, cont2 };

	//creating map(case1)
	Map* map1 = new Map(*continentArray, 2, arrayCountry, 5);

	//creating and printing adjacency matrix
	cout << "Matrix:" << endl;
	map1->setMatrix();
	map1->printMatrix();

	//checking map: if all are not 1s then map is not valid
	cout << "Checking Map:" << endl;
	map1->checkMap();

	//case 2(valid map)
	std::cout << "Case2: Valid Map" << endl;

	int varr0[3] = { 1,3,4 };
	int varr1[3] = { 1,3,5 };
	int varr2[3] = { 2,4,1 };
	int varr3[2] = { 0,2 };
	int varr4[3] = { 1,3,5 };

	Country* vc0 = new Country("c0", 0, varr0, 1, 3, 1);       //name,key,array of neighbor key
	Country* vc1 = new Country("c1", 1, varr1, 1, 3, 2);
	Country* vc2 = new Country("c2", 2, varr2, 1, 3, 3);
	Country* vc3 = new Country("c3", 3, varr3, 2, 2, 4);
	Country* vc4 = new Country("c4", 4, varr4, 2, 3, 5);

	Country* varrayCountry = new Country[5];
	varrayCountry[0] = *vc0;
	varrayCountry[1] = *vc1;
	varrayCountry[2] = *vc2;
	varrayCountry[3] = *vc3;
	varrayCountry[4] = *vc4;

	Map* map2 = new Map(*continentArray, 2, varrayCountry, 5);

	//creating matrix and printing
	cout << "Matrix:" << endl;
	map2->setMatrix();
	map2->printMatrix();
	//checking map(valid)
	cout << "Checking Map:" << endl;
	map2->checkMap();

	//checking if each country is from only one continent
	cout << "Checking continents"<<endl;
	for (int i = 0; i < 5; i++) {

		cout << "Country" << i << ": " << "From Continent:" << varrayCountry[i].getContinentKey()<<endl;

	}

	return 0;


}
