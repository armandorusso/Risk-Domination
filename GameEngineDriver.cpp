#include "GameEngine.h"
#include "GameEngine2.h"
#include "Adapter.h"
/*
int main() {
	Loader* load = new Loader();
	
		int choice = load->menu();

		if (choice == 2) {
			vector<Loader*> games;
			int numGames;
			int numMaps;
			int numPlayers;
			int numTurns;

			cout << "You chose Tournament Mode!";
			string line;

			while (true) {
				cout << "\nNow how many maps would you like to play with?" << endl;

				cin >> line;
				numMaps = stoi(line);
				if (numMaps < 0 || numMaps > 5) {
					cout << "Please chose a number between 1-5" << endl;
					continue;
				}

				else {
					break;
				}

			}

			for (int i = 0; i < numMaps; i++) {
				Loader *load = new Loader();
				games.push_back(load);
				games.at(i)->selectMap();
			}



			while (true) {
				cout << "\nNow how many games would you like to play?" << endl;

				cin >> line;
				numGames = stoi(line);
				if (numGames < 1 || numGames > 5) {
					cout << "Please chose a number between 1-5" << endl;
					continue;
				}

				else {
					break;
				}

			}

			while (true) {
				cout << "\nNow how many turns would you like to play?" << endl;

				cin >> line;
				numTurns = stoi(line);
				cout << numTurns;
				if (numTurns < 3 || numTurns > 50) {
					cout << "Please chose a number between 3-50" << endl;
					continue;
				}

				else {
					break;
				}

			}

			//creating x amount of players
			while (true) {
				string line;
				cout << "Enter a number of players (max is 6, minimum is 2) ";
				cin >> line;
				numPlayers = stoi(line);
				if (numPlayers <= 1) {
					cout << "Enter a player count that's greater than 2 please. Enter another number " << endl;
				}

				else if (numPlayers >= 2 && numPlayers <= 6) {
					break;
				}
			}

			vector<string> names;
			vector<Strategy*> strats; //vector of strategies
			Strategy* strate;

			for (int i = 0; i < numPlayers; i++) { //get the number of players, then loop through numMaps times, then loop thru all players, insert that map
				string choice;
				int strat;
				cout << "What is the strategy you want to use. Any other input will default to benevolent strategy. Enter a number. This is for Player " << (i + 1) << "? " << endl;
				cout << "1. Benevolent Player\n2. Cheater Player\n3. Aggressive Player\n4. Random Player" << endl;
				cin >> choice;
				strat = stoi(choice);
				switch(strat) {
					
				case (1): strate = new BenevolentPlayer(); 
					strats.push_back(strate);
					names.push_back("Benevolent CPU Player");
					break;
				case (2): strate = new CheaterPlayer();
					strats.push_back(strate);
					names.push_back("Cheater CPU Player");
					break;
				case (3): strate = new AggressivePlayer();
					strats.push_back(strate);
					names.push_back("Aggresive CPU Player");
					break;
				case (4): strate = new RandomPlayer(); 
					strats.push_back(strate);
					names.push_back("Random CPU Player");
					break;
				}
				
				
			}


			for (int i = 0; i < numMaps; i++) {
				for (int j = 0; j < numPlayers; j++) {
					Player* p1 = new Player(names.at(j), *(games.at(i)->getMap()), strats.at(i));
					games.at(i)->setPlayers(p1);
				}
			}


			cout << "Now hand of cards are being made: " << endl;

			Deck* deck = new Deck(games.at(0)->getMap()->getCountryCount());

			cout << "Everything is made! You're all good to go on playing! Enjoy playing! :)" << endl;


			for (int i = 0; i < numGames; i++) {
				cout << "========================== GAME " << (i + 1) << " ==========================" << endl;

					Map map = *games.at(i)->getMap();
					vector<Player*> players = *games.at(i)->getPlayers();


					//creating observer for the players
					vector<gameView*>* vectPlayer = new vector<gameView*>;

					for (int i = 0; i < players.size(); i++) {
						vectPlayer->push_back(players.at(i));
					}

					gameObserver* obs = new gameObserver(*vectPlayer);

					//creating game
					Game* game1 = new Game(map, players);

					//startup phase
					game1->startupTournament();
					MainLoop* loop = new MainLoop(*game1);
					loop->setTourney(true); //letting the program know this is tourney mode
					loop->startLoop(numTurns);
					//delete deck;
					if ((i + 1) >= numMaps) { //this is needed since i need to do i+1 when initiliazing a new deck because i already loaded 1 map
						break;
					}
					deck = new Deck(games.at(i + 1)->getMap()->getCountryCount());

				if ((i + 2) == numGames) {

					//printing the winners
					cout << "Here are the winners!" << endl;

					for (int i = 0; i < numGames; i++) {
						cout << "Game " << (i + 1) << endl;
						cout << endl;

						for (int j = 0; j < numMaps; j++) {
							cout << "Map " << (j + 1) << "\t" << loop->getWinners()->at(i) << "\t" << endl;
						}
					}
					

				}
			}

		}


		else if(choice == 1){

			//getting map and players from loader
			Map map = *load->getMap();
			vector<Player*> players = *load->getPlayers();

			//creating observer for the players
			vector<gameView*>* vectPlayer = new vector<gameView*>;

			for (int i = 0; i < players.size(); i++) {
				vectPlayer->push_back(players.at(i));
			}

			gameObserver* obs = new gameObserver(*vectPlayer);

			//creating game
			Game* game1 = new Game(map, players);

			//startup phase
			game1->startupPhase();
			MainLoop* loop = new MainLoop(*game1);

			loop->startLoop(100000000000);
		}

	return 0;
}
*/