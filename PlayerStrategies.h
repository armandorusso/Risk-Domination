#pragma once
#include <iostream>

using namespace std;

class Strategy {
public:
    virtual void execute() = 0;
};

class AggressivePlayer : public Strategy {
public:
    void execute();
};

class HumanPlayer : public Strategy {
public:
    void execute();
};

class BenevolentPlayer : public Strategy {
public:
    void execute();
};

int stratDriver();
