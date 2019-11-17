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

    Country* arrayCountry = player->getMap()->getCountryArray();
    vector<int> attackableCountries = player->getAttackableCountries(player->getMap());
    vector<int> attackableAdjacentCountries;

    cout << "You have the following countries: " << endl;

    for(int i = 0; i< player->getNumOfCountries(); i++) {
        cout << player->getCountriesInts().at(i) << endl;
    }



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

    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(0, attackableAdjacentCountries.size());

    defendingCountry = attackableAdjacentCountries[distribution(generator)];





    //Now that I have the attackable neighbours, now I can choose who to attack.

    //Continue attacking while this country has >= 2 armies && has attackable neighbours

    //update attackable() countries...


    //If size of attackableAdjacentCountries is 0, turn is finished.






}

void AggressivePlayer::executeFortify(Player *player) {

	player->notify(player, "Fortifying");  //notify observer at start of reinforece

	std::cout << std::endl;

	Country* arrayCountry = player->getMap()->getCountryArray();

	//showing countries owned
	cout << "You have the following countries: " << endl;
	for (int i = 0; i < player->getNumOfCountries(); i++) {
		cout << player->getCountriesInts().at(i) << endl;
	}

	int maxArmy=0;
	int countryKeyMax=-1;
	int countryTakingFrom=-1;

	for (int i = 0; i < player->getNumOfCountries(); i++) {

		if (player->getCountriesObjects()->at(i)->getArmy() > maxArmy) {
			maxArmy = player->getCountriesObjects()->at(i)->getArmy();
			countryKeyMax = player->getCountriesObjects()->at(i)->getCountryKey();
		}
	}
	for (int i = 0; i < player->getNumOfCountries(); i++) {

		//takes army from countries that have greater than 1 army to maximize army in agressive country.
		if (player->getCountriesObjects()->at(i)->getArmy() > 1  && player->getCountriesObjects()->at(i)->getCountryKey() != countryKeyMax) {

			countryTakingFrom = player->getCountriesObjects()->at(i)->getCountryKey();
			break;
		}

	}

	//can move country
	if (countryTakingFrom != -1 && countryKeyMax != -1) {

		int army = arrayCountry[countryTakingFrom].getArmy();

		arrayCountry[countryTakingFrom].subtractArmy(army-1);//Giving attacking country max army it can
		arrayCountry[countryKeyMax].addArmy(army-1);

	}
	player->notify(player, "Finished Fortifying");

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

    cout << "Do you wish to attack?" << endl;

    //NO should not happen...
}

void BenevolentPlayer::executeFortify(Player *player) {

	player->notify(player, "Fortifying");  //notify observer at start of reinforece

	std::cout << std::endl;

	Country* arrayCountry = player->getMap()->getCountryArray();

	//showing countries owned
	cout << "You have the following countries: " << endl;
	for (int i = 0; i < player->getNumOfCountries(); i++) {
		cout << player->getCountriesInts().at(i) << endl;
	}

	int maxArmy = 0;
	int minArmy = 100;
	int countryKeyMax = -1;
	int countryGivingTo = -1;
	//getting country that has largest army
	for (int i = 0; i < player->getNumOfCountries(); i++) {

		if (player->getCountriesObjects()->at(i)->getArmy() > maxArmy) {
			maxArmy = player->getCountriesObjects()->at(i)->getArmy();
			countryKeyMax = player->getCountriesObjects()->at(i)->getCountryKey();
		}
	}
	//getting country that has samllest army
	for (int i = 0; i < player->getNumOfCountries(); i++) {

		if (player->getCountriesObjects()->at(i)->getArmy() < minArmy && player->getCountriesObjects()->at(i)->getCountryKey()!=countryKeyMax) {
			minArmy = player->getCountriesObjects()->at(i)->getArmy();
			countryGivingTo = player->getCountriesObjects()->at(i)->getCountryKey();
		}
		cout << "Cannot move more armies" << endl;
	}

	//can move country
	if (countryGivingTo != -1 && countryKeyMax != -1) {

		int army = (arrayCountry[countryKeyMax].getArmy() - arrayCountry[countryGivingTo].getArmy()) / 2;

		arrayCountry[countryKeyMax].subtractArmy(army);  //making both have approzimately eqaul armies.
		arrayCountry[countryGivingTo].addArmy(army);

	}
	player->notify(player, "Finished Fortifying");
}

void BenevolentPlayer::executeReinforce(Player *player) {





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
