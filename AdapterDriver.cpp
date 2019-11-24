#include "ConquestLoader.h"
#include "Adapter.h"

void adapterDriver() {
	
	cout << "Conquest File: " << endl;
	ConquestToOg *adapter = new ConquestToOg();
	MapLoader* loader = new MapLoader();

	adapter->getConquestData("_63_ Planet QUAKE.map");
	Map *map = adapter->convertToOg();

	map->setMatrix();
	cout << "\n";
	map->checkMap();


	for (int i = 0; i < 20; i++) { //this loop is just to skip the lines so we can see both matrices clearly
		cout << "\n";
	}

	cout << "Loader Map: " << endl;

	Map *map2 = loader->getFileData("google.map");
	map2->setMatrix();
	cout << "\n";
	map2->checkMap();
}
