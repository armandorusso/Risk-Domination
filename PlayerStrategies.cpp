#include <iostream>
#include "PlayerStrategies.h"
#include "Player.h"
#include <random>

using namespace std;


void AggressivePlayer::executeAttack(Player *player) {
    player->notify(player, "Attacking"); //notify observer to show initial state

    int attackingCountry; // key for the attacking country
    int defendingCountry; // key for the defending country
    int maxArmy = 0;
    int countryKeyMax;
    Country* maxArmyCountry;

    vector<int> attackableAdjacentCountries;

    do {
        Country* arrayCountry = player->getMap()->getCountryArray();
        vector<int> attackableCountries = player->getAttackableCountries(player->getMap());



        cout << "=========================" << endl;
        cout << "Countries you own" << endl;
        cout << "=========================" << endl;

        for(int i = 0; i< player->getCountryKeys().size(); i++) {
            cout <<player->getCountryKeys().at(i) << endl;
        }

        cout << endl;


        for(int i = 0; i< player->getNumOfCountries(); i++) {
            if(player->getCountriesObjects()->at(i)->getArmy() > maxArmy) {
                maxArmy = player->getCountriesObjects()->at(i)->getArmy();
                countryKeyMax = player->getCountriesObjects()->at(i)->getCountryKey();
            }
        }

        //Always attacking with this country
        vector<int> neighbours;
        Country* maxArmyCountry = getCountryFromCountryKey(countryKeyMax);
        int countryKey = maxArmyCountry->getCountryKey();


        //Can only attack these countries IF attacking country has
        for(int i = 0; i< maxArmyCountry->getNeighbourNum(); i++) {
            neighbours.push_back(maxArmyCountry->getNeighbours()[i]);
        }

        for(int i = 0; i< maxArmyCountry->getNeighbourNum(); i++) {
            vector<int>::iterator it = std::find(attackableCountries.begin(), attackableCountries.end(), neighbours[i]);

            if (it != attackableCountries.end()) {
                attackableAdjacentCountries.push_back(maxArmyCountry->getNeighbours()[i]);
            }
        }

        if(attackableAdjacentCountries.size() == 0) {
            cout << "You can't attack any countries" << endl;
            break;
        }

        cout << "=========================" << endl;
        cout << "Countries you can attack with " << countryKeyMax << endl;
        cout << "=========================" << endl;

        std::random_device r;
        std::default_random_engine generator(r());
        std::uniform_int_distribution<int> distribution(0, attackableAdjacentCountries.size());


        if(attackableAdjacentCountries.size() != 0) {
            defendingCountry = attackableAdjacentCountries[distribution(generator)];
        }else {
            //attack phase() over...
        }

        //Now time to attack the defending country...

        //Attacking conditions are met.
        cout << "Attacking " << defendingCountry << " with " << attackingCountry << endl << endl;

        Player* defendingPlayer = getPlayerFromCountryKey(defendingCountry);
        Player* attackingPlayer = getPlayerFromCountryKey(attackingCountry);

        //printArmiesFromCountries(attackingCountry, defendingCountry);

        //Time to roll the dice for the attacking and defending player.
        player->RollDice(attackingCountry);

        defendingPlayer->RollDice(defendingCountry);

        // Displays the rolls of each player.
        ::displayRoll(*attackingPlayer, *defendingPlayer);

        //If attacking player rolls greater than defending player, defending player loses army. Otherwise, attacking country loses army.
        if (::compareRolls(player, defendingPlayer)) {
            loseArmy(defendingCountry);
        }
        else {
            loseArmy(attackingCountry);
        }

        //If attacking results in 0 armies for the defending player, attacking player adds that country to their list of countries. Defending country is removed
        //from defending player.
        if (getCountryFromCountryKey(defendingCountry)->getArmy() == 0) {

            Country* dCountry = getCountryFromCountryKey(defendingCountry);
            Country* aCountry = getCountryFromCountryKey(attackingCountry);

            player->addCountry(dCountry);
            ::removeCountry(dCountry, defendingPlayer);

            cout << "Country transferred to " << player->getName() << endl;

            //Attacker can transfer 0 to n-1 armies from their country to the country they just won.
            //If user inputs too many armies, appropriate message is displayed and loop is entered.
            if (aCountry->getArmy() > 1) {

                int inputArmies;
                int maxArmiesToTransfer = aCountry->getArmy() - 1;

                cout << "Choose between 0 and " << (aCountry->getArmy() - 1) << " armies to transfer to " << defendingCountry << ": ";
                cout << "1" << "." << endl;
                inputArmies = 1;
                if (inputArmies > maxArmiesToTransfer || inputArmies < 0) {
                    cout << "Invalid number of armies." << endl;
                }

                //Transfer successful.
                cout << "Transfering " << inputArmies << " armies from " << attackingCountry << " to " << defendingCountry << ".\n" << endl;
                dCountry->addArmy(inputArmies);
                aCountry->subtractArmy(inputArmies);
            }
            else {
                cout << "You don't have enough armies to transfer. " << endl;
            }

            //Updating the attackableCountries vector.
            attackableCountries = player->getAttackableCountries(player->getMap());
        }

        printArmiesFromCountries(attackingCountry, defendingCountry);

        //Clearing the currentRoll values in the dice objects, so that
        //more values are not pushed in.
        player->getDice()->getCurrentRoll()->clear();
        defendingPlayer->getDice()->getCurrentRoll()->clear();

    }while(maxArmyCountry->getArmy() >= 2);



    //Now that I have the attackable neighbours, now I can choose who to attack.

    //Continue attacking while this country has >= 2 armies && has attackable neighbours

    //update attackable() countries...


    //If size of attackableAdjacentCountries is 0, turn is finished.


    player->notify(player, "Finished Attacking"); //notify observer to show change after attack.

}

void AggressivePlayer::executeFortify(Player *player) {

}

void AggressivePlayer::executeReinforce(Player *player) {

}

void HumanPlayer::executeAttack(Player *player) {
    player->attack();
}

void HumanPlayer::executeFortify(Player *player) {
    player->fortify();
}

void HumanPlayer::executeReinforce(Player *player) {
    player->reinforce();
}

void BenevolentPlayer::executeAttack(Player *player) {

}

void BenevolentPlayer::executeFortify(Player *player) {

}

void BenevolentPlayer::executeReinforce(Player *player) {

    player->notify(player, "Attacking"); //notify observer to show initial state

    vector<int> attackableCountries = player->getAttackableCountries(player->getMap());

    cout << "=========================" << endl;
    cout << "Countries you own" << endl;
    cout << "=========================" << endl;

    for(int i = 0; i< player->getCountryKeys().size(); i++) {
        cout <<player->getCountryKeys().at(i) << endl;
    }

    cout << endl;

    cout << "=========================" << endl;
    cout << "Countries you can attack" << endl;
    cout << "=========================" << endl;

    for(int i = 0; i< attackableCountries.size(); i++) {
        cout << attackableCountries.at(i) << endl;
    }

    cout << "Do you wish to attack? " << endl;
    cout << "No" << endl;

    player->notify(player, "Finished Attacking"); //notify observer to show change after attack.
}


int stratDriver() {
    return 0;
}

//Driver should demonstrate:

//Different players can be assigned different strategies.
//Should be able to switch between these strategies at any time.

//Notes:
/*
 * Add Strategy Object to Player class
 * Private:
 *  Strategy *strategy;
 *
 *
 *
 * Public:
 *
 * void setStrategy() {
 *
 * }
 *
 * int executeStrategy() {
 * return this->strategy->execute();
 *
 * void setStrategy(Strategy *newStrategy) {
 * this->strategy = newStrategy
 * }
 */