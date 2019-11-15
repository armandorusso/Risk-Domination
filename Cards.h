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
	~Hand();
	//Copy Constructor
	Hand(const Hand &h2);
	//Assignment operator
	Hand& operator=(const Hand &h2);
	bool exchange();
	int* getNumArmies();
	std::vector<std::string>* getCards();
};

class Deck {
	private:
		int* numTotalCards;
	public:
		static std::vector<std::string>* cards;
		Deck(int numCards);
		~Deck();
		//Copy Constructor
		Deck(const Deck &d2);
		//Assignment operator
		Deck& operator=(const Deck& d2);
		void draw(Hand* hand);
		static void shuffle();
		int* getNumTotalCards();
};