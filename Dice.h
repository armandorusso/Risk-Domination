#include <string>
#include <vector>
#ifndef INC_345PROJECT_DICE_H
#define INC_345PROJECT_DICE_H

using std::string;
using std::vector;

class Dice{

private:
     int* numDice = new int();
     int* sum;
     int* totalRolls;
     int* frequencyRolled = new int[6];

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
    int getSum() const;
    void setSum(int sum);
    int *getTotalRolls() const;

};

#endif //INC_345PROJECT_DICE_H
