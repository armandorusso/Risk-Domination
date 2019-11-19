#pragma once
#include "ConquestLoader.h"
#include "MapLoader.h"

class ConquestToOg : public ConquestMap {
private:
	MapLoader* mapLoad;
public:
	ConquestToOg();
	Map* convertToOg(); //adapter method
};