#include "Cards.h"
#include "Player.h"
#include <iostream>

int main() {
	//Create Deck object with 21 cards
	Deck deck(21);

	//Create Map and Player objects
	Player *player1 = new Player("Bojan");

	Continent* cont1 = new Continent();
	Continent* cont2 = new Continent();
	Continent* continentArray[2] = { cont1, cont2 };

	int varr0[3] = { 1,3,4 };
	int varr1[3] = { 2,3 };
	int varr2[2] = { 4,1 };
	int varr3[2] = { 0,2 };
	int varr4[2] = { 1,3 };

	Country* vc0 = new Country("c0", 0, varr0, 1, 3);
	Country* vc1 = new Country("c1", 1, varr1, 1, 2);
	Country* vc2 = new Country("c2", 2, varr2, 1, 2);
	Country* vc3 = new Country("c3", 3, varr3, 2, 2);
	Country* vc4 = new Country("c4", 4, varr4, 2, 2);

	Country* varrayCountry = new Country[5];
	varrayCountry[0] = *vc0;
	varrayCountry[1] = *vc1;
	varrayCountry[2] = *vc2;
	varrayCountry[3] = *vc3;
	varrayCountry[4] = *vc4;

	Map* map2 = new Map(*continentArray, 2, varrayCountry, 5);

	//Setting the adjacency matrix
	map2->setMatrix();

	player1->addCountry(vc0);
	player1->addCountry(vc1);
	player1->addCountry(vc2);
	player1->addCountry(vc3);
	player1->addCountry(vc4);

	//Call reinforce with 5 countries
	std::cout << ("Calling reinforce with 5 countries-----------------\n");
	player1->reinforce();

	//Fill player1 hand with 10 cards
	for (int i = 0; i < 10; i++) {
		deck.draw(*player1->getHand());
	}

	//Print the hand after drawing 10 cards
	std::cout << "PLAYER1 HAND-----------";
	std::cout << "\n";
	for (int i = 0; i < player1->getHand()->getCards()->size(); i++) {
		std::cout << (*player1->getHand()->getCards())[i];
		std::cout << "\n";
	}

	//Call reinforce with 10 cards
	std::cout << ("Calling reinforce with 10 cards----------------------\n");
	player1->reinforce();

	//Print the hand after exchanging cards
	std::cout << "PLAYER1 HAND-----------";
	std::cout << "\n";
	for (int i = 0; i < player1->getHand()->getCards()->size(); i++) {
		std::cout << (*player1->getHand()->getCards())[i];
		std::cout << "\n";
	}

	return 0;
}