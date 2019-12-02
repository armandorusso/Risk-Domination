#include "GameEngine.h"
#include "GameEngine2.h"
#include "Adapter.h"

int main() {
	Loader* load = new Loader();
	
		int choice = load->menu();

		if (choice == 2) {
			vector<Loader*>* games = new vector<Loader*>;
			vector<Loader*>* mapsPlay = new vector<Loader*>;
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


			vector<vector<Loader*>*>* allMaps = new vector<vector<Loader*>*>;
			
			for (int i = 0; i < numMaps; i++) {
				
				cout << "Please enter the map file name you wish to load : " << endl;

				string file;
				cin >> file;

				vector<Loader*>* gamesM = new vector<Loader*>;
		        
				for (int j = 0; j < numGames; j++) {
					Loader* load = new Loader();
					gamesM->push_back(load);
					gamesM->at(j)->selectMap2(file);
				}
				allMaps->push_back(gamesM);
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
			vector<Strategy*>* strats = new vector<Strategy*>; //vector of strategies
			Strategy* strate;

			for (int i = 0; i < numPlayers; i++) { //get the number of players, then loop through numMaps times, then loop thru all players, insert that map
				string choice;
				int strat;
				cout << "What is the strategy you want to use. Any other input will default to benevolent strategy. Enter a number. This is for Player " << (i + 1) << "? " << endl;
				cout << "1. Benevolent Player\n2. Cheater Player\n3. Aggressive Player\n4. Random Player" << endl;
				cin >> choice;
				strat = stoi(choice);
				string name;
				switch(strat) {
					
				case (1): strate = new BenevolentPlayer(); 
					strats->push_back(strate);
					name = "BenevolentCPUPlayer" + i;
					names.push_back(name);
					break;
				case (2): strate = new CheaterPlayer();
					strats->push_back(strate);
					name = "CheaterCPUPlayer" + i;
					names.push_back(name);
					break;
				case (3): strate = new AggressivePlayer();
					strats->push_back(strate);
					name = "AggresiveCPUPlayer" + i;
					names.push_back(name);
					break;
				case (4): strate = new RandomPlayer(); 
					strats->push_back(strate);
					name = "RandomCPUPlayer" + i;
					names.push_back(name);
					break;
				}
				
				
			}


			for (int i = 0; i < numMaps; i++) {
				
				for (int j = 0; j < numGames; j++) {

                  for (int k = 0; k < numPlayers; k++) {
					Player* p1 = new Player(names.at(k), *(allMaps->at(i)->at(j)->getMap()), strats->at(k));
					allMaps->at(i)->at(j)->setPlayers(p1);
				  }

				}
				
				
			}


			cout << "Now hand of cards are being made: " << endl;

			Deck* deck = new Deck(allMaps->at(0)->at(0)->getMap()->getCountryCount());

			cout << "Everything is made! You're all good to go on playing! Enjoy playing! :)" << endl;


			//vector that store winners
			vector<vector<Player*>*> winners;

			for (int h = 0; h < numMaps; h++) {
				winners.push_back(new vector<Player*>);
			}


			for (int i = 0; i < numMaps; i++) {
				   
				
				
					cout << "========================== Map " << (i + 1) << " ==========================" << endl;

					
					for (int j = 0; j < numGames; j++) {
						
						
						cout << "========================== Game " << (j + 1) << " ==========================" << endl;
						
						
						Map* map = allMaps->at(i)->at(j)->getMap();
						vector<Player*>* players = allMaps->at(i)->at(j)->getPlayers();

						map->setPlayer(players);

						//creating observer for the players
						vector<gameView*>* vectPlayer = new vector<gameView*>;

						for (int i = 0; i < players->size(); i++) {
							vectPlayer->push_back(players->at(i));
						}

						gameObserver* obs = new gameObserver(*vectPlayer);

						//creating game
						
                        Game* game1 = new Game(*map, *players);
						

							//startup phase
							game1->startupTournament();
							MainLoop* loop = new MainLoop(*game1);
							loop->setTourney(true); //letting the program know this is tourney mode
							Player* winner = loop->startLoop(numTurns);
							//delete deck;
							
							winners.at(i)->push_back(winner);

							
							deck = new Deck(allMaps->at(i)->at(j)->getMap()->getCountryCount());
						
						
					}
		    }
			//showing winners
			int size1 = winners.size();
			for (int f = 0; f < size1; f++) {
				cout << endl;
				cout << "Winner of Map " << f<<endl;
				cout << endl;
				int size2 = winners.at(f)->size();
				for (int s = 0; s < size2; s++) {
					cout << endl;
					cout << "winner of game " << s << endl;
					if (winners.at(f)->at(s) == NULL) {
						cout << "Draw" << endl;
					}
					else
						cout << winners.at(f)->at(s)->getName();
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
