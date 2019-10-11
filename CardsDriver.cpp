#include "Cards.h"
#include <iostream>

int main() {
	//Create Deck object and print the deck
	Deck deck;
	int num = *deck.getNumTotalCards();
	int numArt = 0;
	int numCav = 0;
	int numInf = 0;

	std::cout << "Number of cards: " + std::to_string(num) + "\n";
	for (int i = 0; i < Deck::cards->size(); i++) {
		std::cout << (*Deck::cards)[i];
		std::cout << "\n";
		if ((*Deck::cards)[i] == cardType.artillery)
			numArt++;
		else if ((*Deck::cards)[i] == cardType.cavalry)
			numCav++;
		else
			numInf++;
	}
	//Print amount of each card type
	std::cout << "Infantry: " + std::to_string(numInf) + ", Cavalry: " + std::to_string(numCav) + ", Artillery: " + std::to_string(numCav) + "\n";

	//Create Hand object and fill with 10 cards
	Hand hand;
	for (int i = 0; i < 10; i++) {
		deck.draw(hand);
	}

	//Print the hand after drawing 10 cards
	std::cout << "HAND-----------";
	std::cout << "\n";
	for (int i = 0; i < hand.getCards()->size(); i++) {
		std::cout << (*hand.getCards())[i];
		std::cout << "\n";
	}

	//Exchange 3 times and print the hand after the exchange
	hand.exchange();
	std::cout << "AFTER EXCHANGE-----------";
	std::cout << "\n";
	for (int i = 0; i < hand.getCards()->size(); i++) {
		std::cout << (*hand.getCards())[i];
		std::cout << "\n";
	}
	hand.exchange();
	std::cout << "AFTER EXCHANGE-----------";
	std::cout << "\n";
	for (int i = 0; i < hand.getCards()->size(); i++) {
		std::cout << (*hand.getCards())[i];
		std::cout << "\n";
	}
	hand.exchange();
	std::cout << "AFTER EXCHANGE-----------";
	std::cout << "\n";
	for (int i = 0; i < hand.getCards()->size(); i++) {
		std::cout << (*hand.getCards())[i];
		std::cout << "\n";
	}
	std::cout << "DECK AFTER EXCHANGE-----------";
	std::cout << "\n";
	for (int i = 0; i < Deck::cards->size(); i++) {
		std::cout << (*Deck::cards)[i];
		std::cout << "\n";
	}

	return 0;
}