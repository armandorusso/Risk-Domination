#pragma once
#include <vector>
#include <string>

static struct CardType {
	std::string infantry = "Infantry";
	std::string artillery = "Artillery";
	std::string cavalry = "Cavalry";
} cardType;

class Hand {
private:
	std::vector<std::string>* cards;
	int* numArmies;
public:
	Hand();
	void exchange();
	int* getNumArmies();
	std::vector<std::string>* getCards();
};

class Deck {
	private:
		int* numTotalCards;
	public:
		static std::vector<std::string>* cards;
		Deck();
		void draw(Hand hand);
		static void shuffle();
		int* getNumTotalCards();
};