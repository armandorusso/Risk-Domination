#include <string>
#include "Dice.h"
#include "Dice.h"
#include <iostream>
#include <random>
#include <vector>

//https://github.com/armandorusso/Risk-Domination.git


//This method prints the contents of a vector to the console.
void displayRolls(vector<int> container) {
    std::cout << "[";
    for(int i = 0; i<container.size(); i++) {
        if(i == container.size()-1) {
            std::cout << container.at(i);
        }else {
            std::cout << container.at(i) << " ";
        }
    }
    std::cout << "]" << std::endl;
}

//Constructor for the Dice class. Takes in the number of dice as a parameter.
Dice::Dice(int numDice) {
    this->totalRolls = new int(0);

    this->setNumDice(numDice);

    for(int i = 0; i < 6; i++) {
        frequencyRolled[i] = 0;
    }
}

Dice::Dice(const Dice &dice) {
    std::cout << "Creating copy..." << std::endl;

}

//Constructor for the Dice class. Takes in the number of dice as a parameter.
Dice::Dice() {
    this->totalRolls = new int(0);

    this->setNumDice(0);

    for(int i = 0; i < 6; i++) {
        (frequencyRolled[i]) = 0;
    }

}

//Destructor for the Dice class. It sets all data members to nullptr.
Dice::~Dice() {
    delete numDice;
    numDice = nullptr;

    delete sum;
    sum = nullptr;

    delete totalRolls;
    totalRolls = nullptr;

    delete [] frequencyRolled;
    frequencyRolled = nullptr;
}

//Loops through the frequencyRolled array in the Dice class. Displays
//the number of times that the values have been rolled for the current Dice object.
//Example: [0 1 2 3 4 5] : 1 rolled 0 times, 2 rolled 1 time, 3 rolled 2 times, etc.
void Dice::printFrequency() {
    for(int i = 0; i<6; i++) {
        std::cout << i+1 << " was rolled: " << (this->frequencyRolled[i]) << " times. " << std::endl;
    }

    std::cout << std::endl;
}

//Displays the frequency of each dice roll value as a percentage of total rolls for the current
//Dice object.
void Dice::displayPercentage() {
    for(int i = 0; i<6; ++i) {
        std::cout << (i+1) << " was rolled ";
        std::cout << static_cast<double>((this->frequencyRolled)[i])/(*this->totalRolls) * 100 << "% of the time." << std::endl;
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

    vector<int> currentRoll;

    int dice_roll;

    for(int i = 0; i<(*this->getNumDice()); i++) {
        ++(*this->totalRolls);

        dice_roll = distribution(generator);
        currentRoll.push_back(dice_roll);

        if (dice_roll > 6 || dice_roll < 1) {
            std::cout << "Error" << std::endl;
            exit(0);
        }

        switch(dice_roll) {
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

    displayRolls(currentRoll);
    currentRoll.clear();
}

void Dice::swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


//=================
//BEGIN Getters and Setters
//=================
int *Dice::getNumDice() const {
    return numDice;
}

void Dice::setNumDice(int numDice) {
    if (numDice > 3) {
        *Dice::numDice = 3;
    } else if (numDice <1) {
        *Dice::numDice = 1;
    } else {
        *Dice::numDice = numDice;
    }
}

int Dice::getSum() const {
    return *sum;
}

void Dice::setSum(int sum) {
    *Dice::sum = sum;
}

int *Dice::getTotalRolls() const  {
    return totalRolls;
}
//=================
//END Getters and Setters
//=================


//int main() {
//
//
//    //Choosing the number of dice each player will roll.
//    std::cout << "How many dice do you want to roll? " << std::endl;
//
//
//
//    Dice* dice1 = new Dice();
//
//    for(int i = 0; i<10; i++) { //Rolling the dice 10 times
//        dice1 -> Roll();
//    }
//
//    dice1->printFrequency();
//
//    dice1->displayPercentage();
//
//
//    delete dice1;
//
//
//    return 0;
//}
