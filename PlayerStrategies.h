#pragma once
#include <iostream>

using namespace std;

class Strategy {
    virtual void execute() = 0;
};

class AggressivePlayer : public Strategy {
    void execute();
};

class HumanPlayer : public Strategy {
    void execute();
};

class BenevolentPlayer : public Strategy {
    void execute();
};

int stratDriver();
