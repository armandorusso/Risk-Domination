#include "Cards.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>

Hand::Hand() {
	this->cards = new std::vector<std::string>(0);
	this->numArmies = new int(0);
}

Hand::~Hand() {
	delete cards;
	delete numArmies;

	cards = nullptr;
	numArmies = nullptr;
}

//Copy Constructor
Hand::Hand(const Hand &h2) {
	cards = new std::vector<std::string>(0);
	numArmies = new int(0);
	cards = h2.cards;
	numArmies = h2.numArmies;
}
//Assignment operator
Hand& Hand::operator=(const Hand& h2) {
	Hand::operator=(h2);
	cards = h2.cards;
	numArmies = h2.numArmies;
	return *this;
}

//Exchange cards for armies
bool Hand::exchange() {
	int infCounter = 0;
	int artCounter = 0;
	int cavCounter = 0;
	std::string exchangeType = "";

	//Find the type of exchange (3 of the same type or 1 of each)
	for (int i = 0; i < this->cards->size(); i++) {
		if ((*this->cards)[i] == cardType.infantry) {
			infCounter++;
			if (infCounter >= 3) {
				exchangeType = cardType.infantry;
				break;
			}
		}
		else if ((*this->cards)[i] == cardType.artillery) {
			artCounter++;
			if (artCounter >= 3) {
				exchangeType = cardType.artillery;
				break;
			}
		}
		else if ((*this->cards)[i] == cardType.cavalry) {
			cavCounter++;
			if (cavCounter >= 3) {
				exchangeType = cardType.cavalry;
				break;
			}
		}
		if (infCounter > 0 && artCounter > 0 && cavCounter > 0) {
			exchangeType = "all";
			break;
		}
	}

	//Remove exchanged cards from hand and add in deck
	if (exchangeType.empty()) {
		std::cout << "\nYou cannot exchange cards.\n";
		return false;
	}
	else if (exchangeType != "all") {
		int counter = 0;
		for (int i = 0; i < this->cards->size(); i++) {
			if ((*this->cards)[i] == exchangeType) {
				(*this->cards)[i] = "empty";
				counter++;
			}
			if (counter == 3) {
				(*Deck::cards).push_back(exchangeType);
				(*Deck::cards).push_back(exchangeType);
				(*Deck::cards).push_back(exchangeType);
				(*this->numArmies) = (*this->numArmies) + 5;
				break;
			}
		}
		std::cout << "\nYou exchanged 3 " + exchangeType + " cards for " + std::to_string(*this->numArmies) + " armies.\n";
		Deck::shuffle();
	}
	else {
		bool gotInf = false;
		bool gotArt = false;
		bool gotCav = false;
		int counter = 0;
		for (int i = 0; i < this->cards->size(); i++) {
			if ((*this->cards)[i] == cardType.infantry && !gotInf) {
				(*this->cards)[i] = "empty";
				counter++;
				gotInf = true;
				(*Deck::cards).push_back(cardType.infantry);
			}
			if ((*this->cards)[i] == cardType.artillery && !gotArt) {
				(*this->cards)[i] = "empty";
				counter++;
				gotArt = true;
				(*Deck::cards).push_back(cardType.artillery);
			}
			if ((*this->cards)[i] == cardType.cavalry && !gotCav) {
				(*this->cards)[i] = "empty";
				counter++;
				gotCav = true;
				(*Deck::cards).push_back(cardType.cavalry);
			}
		}
		*this->numArmies = *this->numArmies + 5;
		std::cout << "\nExchanged one of each card type for " + std::to_string(*this->numArmies) + " armies.\n";
	}
	//Clean up hand vector (remove empty elements)
	std::vector<std::string>::iterator i = (*this->cards).begin();
	while (i != (*this->cards).end())
	{
		if (i->find("empty", 0) != std::string::npos)
		{
			i = (*this->cards).erase(i);
		}
		else
		{
			++i;
		}
	}
	return true;
}

int* Hand::getNumArmies() {
	return this->numArmies;
}

std::vector<std::string>* Hand::getCards() {
	return this->cards;
}

std::vector<std::string>* Deck::cards;
Deck::Deck(int numCards) {
	this->numTotalCards = new int(numCards);
	int numberOfCountries = *numTotalCards;
	Deck::cards = new std::vector<std::string>(numCards);

	//Populate the cards vector with an equal number of different cardTypes
	int tempNum = 0;
	for (int i = 0; i < numberOfCountries; i++) {
		if (tempNum == 0) {
			(*Deck::cards)[i] = cardType.infantry;
			tempNum++;
		}
		else if (tempNum == 1) {
			(*Deck::cards)[i] = cardType.artillery;
			tempNum++;
		}
		else {
			(*Deck::cards)[i] = cardType.cavalry;
			tempNum = 0;
		}
	}
	//Shuffle the deck once it has been populated
	this->shuffle();
}

Deck::~Deck() {
	delete numTotalCards;

	numTotalCards = nullptr;
}

//Copy Constructor
Deck::Deck(const Deck &d2) {
	numTotalCards = new int(0);
	numTotalCards = d2.numTotalCards;
}
//Assignment operator
Deck& Deck::operator=(const Deck& d2) {
	Deck::operator=(d2);
	numTotalCards = d2.numTotalCards;
	return *this;
}

//Generate a random number and shuffle the cards vector
void Deck::shuffle() {
	std::default_random_engine engine;
	engine.seed(time(0));
	auto rng = engine;
	std::shuffle(std::begin(*Deck::cards), std::end(*Deck::cards), rng);
}

//Draw the first non-empty card from the cards vector
void Deck::draw(Hand* hand) {
	std::string cardDrawn;
	for (int i = 0; i < Deck::cards->size(); i++) {
		if (!(*Deck::cards)[i].empty()) {
			cardDrawn = (*Deck::cards)[i];
			//The card at index i will be drawn, so make that index empty
			(*Deck::cards).erase((*Deck::cards).begin() + i);
			break;
		}
	}
	hand->getCards()->push_back(cardDrawn);
}

int* Deck::getNumTotalCards() {
	return this->numTotalCards;
}