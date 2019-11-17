#include <string>
#include <iostream>
#include <random>
#include <vector>

#include "Dice.h"

using namespace std;


//Constructor for the Dice class. Takes in the number of dice as a parameter.
Dice::Dice(int numDice) {
	this->numDice = new int(0);
	this->highestRoll = new int(0);
	this->totalRolls = new int(0);
	this->setNumDice(numDice);
	this->frequencyRolled = new int[6];
	this->setHighestRoll(0);

	for (int i = 0; i < 6; i++) {
		frequencyRolled[i] = 0;
	}
}

Dice::Dice(const Dice &dice) {
    numDice = new int (*dice.numDice);
    highestRoll = new int (*dice.highestRoll);
    totalRolls = new int (*dice.totalRolls);
    frequencyRolled = new int[6];

    for(int i = 0; i< 6; i++) {
        frequencyRolled[i] = dice.frequencyRolled[i];
    }

}

//Constructor for the Dice class. Takes in the number of dice as a parameter.
Dice::Dice() {
	this->numDice = new int(0);
	this->highestRoll = new int(0);
	this->totalRolls = new int(0);
	this->setNumDice(1);
	this->setHighestRoll(0);
	this->frequencyRolled = new int[6];

	for (int i = 0; i < 6; i++) {
		(frequencyRolled[i]) = 0;
	}
}



//Destructor for the Dice class. It sets all data members to nullptr.
Dice::~Dice() {
	delete numDice;
	numDice = nullptr;

	delete highestRoll;
	highestRoll = nullptr;

	delete roll;
	roll = nullptr;

	delete totalRolls;
	totalRolls = nullptr;

	delete[] frequencyRolled;
	frequencyRolled = nullptr;
}

//This method prints the contents of a vector to the console.
void Dice::displayRolls(vector<int> container) {
	std::cout << "[";

	for (int i = 0; i<container.size(); i++) {
		if (i == container.size() - 1) {
			std::cout << container.at(i);
		}
		else {
			std::cout << container.at(i) << " ";
		}
	}
	std::cout << "]" << std::endl;
}

//Loops through the frequencyRolled array in the Dice class. Displays
//the number of times that the values have been rolled for the current Dice object.
//Example: [0 1 2 3 4 5] : 1 rolled 0 times, 2 rolled 1 time, 3 rolled 2 times, etc.
void Dice::printFrequency() {
	for (int i = 0; i<6; i++) {
		std::cout << i + 1 << " was rolled: " << (this->frequencyRolled[i]) << " times. " << std::endl;
	}

	std::cout << std::endl;
}

//Displays the frequency of each dice roll value as a percentage of total rolls for the current
//Dice object.
void Dice::displayPercentage() {
	for (int i = 0; i<6; ++i) {

		double percentage = static_cast<double>((this->frequencyRolled)[i]) / (*this->totalRolls) * 100;

		std::cout << (i + 1) << " was rolled ";
		printf("%.2f", percentage);
		std::cout << "% of the time." << std::endl;
	}

	std::cout << std::endl;
}


//Rolls the Dice object.
//Random number between 1-6 is generated. Increments the appropriate index of the frequencyRolled array in the Dice class.
//Places the contents of the roll in a vector, sorts it, and displays it to the console.
void Dice::Roll() {
	std::random_device r;
	std::default_random_engine generator(r());
	std::uniform_int_distribution<int> distribution(1, 6);

	int numDice = *this->getNumDice();
	vector<int> currentRoll;

	this->roll = new vector<int>(numDice);
	int dice_roll;

	for (int i = 0; i<(numDice); i++) {
		++(*this->totalRolls);

		dice_roll = distribution(generator);

		currentRoll.push_back(dice_roll);

		if (dice_roll > 6 || dice_roll < 1) {
			std::cout << "Error" << std::endl;
			exit(0);
		}

		switch (dice_roll) {
		case 1:
			++((this->frequencyRolled)[0]);
			break;
		case 2:
			++((this->frequencyRolled)[1]);
			break;
		case 3:
			++((this->frequencyRolled)[2]);
			break;
		case 4:
			++((this->frequencyRolled)[3]);
			break;
		case 5:
			++((this->frequencyRolled)[4]);
			break;
		case 6:
			++((this->frequencyRolled)[5]);
			break;

		default:
			std::cout << "Not an appropriate variable" << std::endl;
			break;
		}
	}

	sort(currentRoll.begin(), currentRoll.end());

	for (int i = 0; i<numDice; i++) {
		(*roll)[i] = currentRoll[i];
	}

	setHighestRoll(currentRoll[currentRoll.size() - 1]);
	currentRoll.clear();

	std::cout << std::endl;
}


//=================
//BEGIN Getters and Setters
//=================

int *Dice::getNumDice() const {
	return numDice;
}

void Dice::setNumDice(int numDice) {
	if (numDice > 3 || numDice < 1) {
		std::cout << "Invalid number of Dice" << std::endl;
	}
	else {
		*this->numDice = numDice;
	}
}

int *Dice::getTotalRolls() const {
	return totalRolls;
}

void Dice::setHighestRoll(int num) {
	*Dice::highestRoll = num;
}

int *Dice::getHighestRoll() const {
	return highestRoll;
}

vector<int> *Dice::getCurrentRoll() const {
	return roll;
}
//=================
//END Getters and Setters
//=================


const Dice& Dice::operator=(const Dice& r) {
    if(&r != this) {
        delete numDice;
        delete highestRoll;
        delete roll;
        delete totalRolls;
        delete[] frequencyRolled;

        numDice = new int(*r.numDice);
        highestRoll = new int(*r.highestRoll);
        totalRolls = new int(*r.totalRolls);
        frequencyRolled = new int[6];

        for(int i = 0; i< 6; i++) {
            frequencyRolled[i] = r.frequencyRolled[i];
        }
        roll = new vector<int>(*r.numDice);

        for(int i = 0; i< roll->size(); i++) {
            roll->push_back(r.roll->at(i));
        }
    }
    return *this;

}
