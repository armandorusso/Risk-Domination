#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Dice{

private:
    int* numDice;
    int* totalRolls;
    int* frequencyRolled;
    int* sum;
    int* highestRoll;

public:
    Dice(int numDice);
    Dice(const Dice&);
    Dice();
    ~Dice();
    void swap(int* a, int* b);
    void printFrequency();
    void displayPercentage();
    void Roll();

    int *getNumDice() const;
    void setNumDice(int num);
    int *getTotalRolls() const;
    void setHighestRoll(int num);
    int *getHighestRoll() const;
};

int diceDriver();
