#include <iostream>
#include "PlayerStrategies.h"
#include "Player.h"
#include <random>

using namespace std;



void AggressivePlayer::executeAttack(Player *player) {

    cout << "What's happening" << endl;
    player->notify(player, "Attacking"); //notify observer to show initial state

    int attackingCountry = -1; // key for the attacking country
    int defendingCountry = -1; // key for the defending country
    int maxArmy = 0;
    int countryKeyMax;
    Country* maxArmyCountry =NULL;

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

	player->notify(player, "Fortifying");  //notify observer at start of reinforece

	std::cout << std::endl;

	Country* arrayCountry = player->getMap()->getCountryArray();

	//showing countries owned
	cout << "You have the following countries: " << endl;
	for (int i = 0; i < player->getNumOfCountries(); i++) {
		cout << player->getCountriesInts().at(i) << endl;
	}

	int maxArmy = 0;
	int countryKeyMax = -1;
	int countryTakingFrom = -1;

	for (int i = 0; i < player->getNumOfCountries(); i++) {

		if (player->getCountriesObjects()->at(i)->getArmy() > maxArmy) {
			maxArmy = player->getCountriesObjects()->at(i)->getArmy();
			countryKeyMax = player->getCountriesObjects()->at(i)->getCountryKey();
		}
	}
	for (int i = 0; i < player->getNumOfCountries(); i++) {

		//takes army from countries that have greater than 1 army to maximize army in agressive country.
		if (player->getCountriesObjects()->at(i)->getArmy() > 1 && player->getCountriesObjects()->at(i)->getCountryKey() != countryKeyMax) {

			countryTakingFrom = player->getCountriesObjects()->at(i)->getCountryKey();
			break;
		}

	}

	//can move country
	if (countryTakingFrom != -1 && countryKeyMax != -1) {

		int army = arrayCountry[countryTakingFrom].getArmy();

		arrayCountry[countryTakingFrom].subtractArmy(army - 1);//Giving attacking country max army it can
		arrayCountry[countryKeyMax].addArmy(army - 1);

	}
	player->notify(player, "Finished Fortifying");

}

void AggressivePlayer::executeReinforce(Player *player) {

	player->notify(player, "Reinforcing");

	//std::cout << this->getName() << " is reinforcing..." << std::endl;

	int armiesToExchange = 0;

	//GET ARMIES FOR COUNTRIES
	armiesToExchange = player->getNumCountries() / 3;

	//Must get minimum 3 armies
	if (armiesToExchange < 3) {
		armiesToExchange = 3;
	}

	//GET ARMIES FROM CONTINENT-CONTROL VALUE
	armiesToExchange = armiesToExchange + player->checkIfOwnCont();

	//EXCHANGE CARDS FOR ARMIES
	while (player->getHand()->exchange()) {
		armiesToExchange = armiesToExchange + *player->getHand()->getNumArmies();
	}

	//Aggressive Player

	//Get index of country with most armies
	int strongestCountryIndex = 0;
	for (int i = 0; i < player->getCountriesObjects()->size(); i++) {
		if (player->getCountriesObjects()->at(i)->getArmy() > player->getCountriesObjects()->at(strongestCountryIndex)->getArmy()) {
			strongestCountryIndex = i;
		}
	}

	//Distribute all armies to the strongest country
	player->getCountriesObjects()->at(strongestCountryIndex)->addArmy(armiesToExchange);
	player->getMap()->getCountryArray()[player->getCountriesObjects()->at(strongestCountryIndex)->getCountryKey()].addArmy(armiesToExchange);

	player->notify(player, "Finished Reinforcing");
}

void HumanPlayer::executeAttack(Player *player) {
    player->attack();
}

void HumanPlayer::executeFortify(Player *player) {
    player->fortify();
}

void HumanPlayer::executeReinforce(Player *player) {

	player->notify(player, "Reinforcing");

	//std::cout << this->getName() << " is reinforcing..." << std::endl;

	int armiesToExchange = 0;

	//GET ARMIES FOR COUNTRIES
	armiesToExchange = player->getNumCountries() / 3;

	//Must get minimum 3 armies
	if (armiesToExchange < 3) {
		armiesToExchange = 3;
	}

	//GET ARMIES FROM CONTINENT-CONTROL VALUE
	armiesToExchange = armiesToExchange + player->checkIfOwnCont();

	//EXCHANGE CARDS FOR ARMIES
	while (player->getHand()->exchange()) {
		armiesToExchange = armiesToExchange + *player->getHand()->getNumArmies();
	}

	//Human Player

	//Distribute all armies
	while (armiesToExchange != 0) {

		//Display the number of armies to distribute and a list of owned countries
		std::cout << std::endl << "You have " << armiesToExchange << " armies left to distribute." << std::endl;
		std::cout << "Here are the countries you own:" << std::endl;

		for (int i = 0; i < player->getCountriesObjects()->size(); i++) {
			std::cout << "Country key: " << player->getCountriesObjects()->at(i)->getCountryKey() << ", Armies: " << player->getCountriesObjects()->at(i)->getArmy() << std::endl;
		}

		//Get the country the player wants to reinforce
		int chosenKey = 0;
		std::cout << "Which country do you want to reinforce?" << std::endl;
		std::cin >> chosenKey;

		//Check if the player owns the chosen country key
		bool validKey = false;
		do {
			for (int i = 0; i < player->getCountriesObjects()->size(); i++) {
				if (player->getCountriesObjects()->at(i)->getCountryKey() == chosenKey) {
					validKey = true;
				}
			}

			if (!validKey) {
				std::cout << "Please enter a valid country key." << std::endl;
				std::cin >> chosenKey;
			}
		} while (!validKey);

		//Get the number of armies the player wants to distribute to the chosen country
		int chosenArmies = 0;
		std::cout << "You have " << armiesToExchange << " armies left to distribute." << std::endl;
		std::cout << "How many armies do you want to distribute?" << std::endl;
		std::cin >> chosenArmies;

		//Validate number of armies input
		while (chosenArmies > armiesToExchange || chosenArmies < 1) {
			std::cout << "Please enter a valid number of armies" << std::endl;
			std::cin >> chosenArmies;
		}

		//Distribute the armies in the chosen country
		for (int i = 0; i < player->getCountriesObjects()->size(); i++) {
			if (player->getCountriesObjects()->at(i)->getCountryKey() == chosenKey) {
				player->getCountriesObjects()->at(i)->addArmy(chosenArmies);
				player->getMap()->getCountryArray()[player->getCountriesObjects()->at(i)->getCountryKey()].addArmy(chosenArmies);
			}
		}

		//Display how many countries were distributed to which country
		std::cout << "Distributed " << chosenArmies << " armies to country " << chosenKey << std::endl;

		//Reduce the number of armies left to exchange
		armiesToExchange = armiesToExchange - chosenArmies;
	}

	player->notify(player, "Finished Reinforcing");
}

void BenevolentPlayer::executeAttack(Player *player) {

	player->notify(player, "Attacking"); //notify observer to show initial state

	vector<int> attackableCountries = player->getAttackableCountries(player->getMap());

	cout << "=========================" << endl;
	cout << "Countries you own" << endl;
	cout << "=========================" << endl;

	for (int i = 0; i < player->getCountryKeys().size(); i++) {
		cout << player->getCountryKeys().at(i) << endl;
	}

	cout << endl;

	cout << "=========================" << endl;
	cout << "Countries you can attack" << endl;
	cout << "=========================" << endl;

	for (int i = 0; i < attackableCountries.size(); i++) {
		cout << attackableCountries.at(i) << endl;
	}

	cout << "Do you wish to attack? " << endl;
	cout << "No" << endl;

	player->notify(player, "Finished Attacking"); //notify observer to show change after attack.



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

		if (player->getCountriesObjects()->at(i)->getArmy() < minArmy && player->getCountriesObjects()->at(i)->getCountryKey() != countryKeyMax) {
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

	player->notify(player, "Reinforcing");

	//std::cout << this->getName() << " is reinforcing..." << std::endl;

	int armiesToExchange = 0;

	//GET ARMIES FOR COUNTRIES
	armiesToExchange = player->getNumCountries() / 3;

	//Must get minimum 3 armies
	if (armiesToExchange < 3) {
		armiesToExchange = 3;
	}

	//GET ARMIES FROM CONTINENT-CONTROL VALUE
	armiesToExchange = armiesToExchange + player->checkIfOwnCont();

	//EXCHANGE CARDS FOR ARMIES
	while (player->getHand()->exchange()) {
		armiesToExchange = armiesToExchange + *player->getHand()->getNumArmies();
	}

	//Benevolent Player

	//Distribute 1 army at a time to the weakest country
	int index = 0;
	while (armiesToExchange != 0) {
		if (index == player->getCountriesObjects()->size()) {
			index = 0;
		}

		//Get the index of the country with the least amount of armies
		int weakestCountryIndex = 0;
		for (int i = 0; i < player->getCountriesObjects()->size(); i++) {
			if (player->getCountriesObjects()->at(i)->getArmy() < player->getCountriesObjects()->at(weakestCountryIndex)->getArmy()) {
				weakestCountryIndex = i;
			}
		}

		//Distribute 1 army to the weakest country
		player->getCountriesObjects()->at(weakestCountryIndex)->addArmy(1);
		player->getMap()->getCountryArray()[player->getCountriesObjects()->at(weakestCountryIndex)->getCountryKey()].addArmy(1);

		armiesToExchange--;
		index++;
	}

	player->notify(player, "Finished Reinforcing");
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