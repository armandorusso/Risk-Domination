
#include"GameEngine2.h"
#include"GameEngine.h"

/*int main() {

	Loader *load = new Loader();

	load->menu();

	//getting map and players from loader
	Map map = *load->getMap();
	vector<Player*> players = *load->getPlayers();

	//creating observer for the players
	vector<gameView*>* vectPlayer = new vector<gameView*>;
	
	for (int i = 0; i < players.size(); i++) {
		vectPlayer->push_back(players.at(i));
	}

	gameObserver* obs = new gameObserver(*vectPlayer);

	//creting game
	Game *game1 = new Game(map, players);

	//startup phase
	game1->startupPhase();
	MainLoop* loop = new MainLoop(*game1);

	loop->startLoop();


}
*/