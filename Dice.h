#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Dice {

private:
	int* numDice;
	int* totalRolls;
	int* frequencyRolled;
	int* highestRoll;
	vector<int> *roll;

public:
	Dice(int numDice);
	Dice(const Dice&);
	Dice();
	~Dice();
	void printFrequency();
	void displayPercentage();
	void displayRolls(vector<int> container);
	void Roll();

	int *getNumDice() const;
	void setNumDice(int num);

	vector<int> *getCurrentRoll() const;

	int *getTotalRolls() const;
	void setHighestRoll(int num);
	int *getHighestRoll() const;

	const Dice& operator=(const Dice& r);
};
