#include "Grid.h"
#include "Market.h"
#include "Database.h"
#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));
    Market* mark = new Market;		// items && spells
	Database* dt = new Database;	// livings(heroes && monsters)
	Grid game(mark, dt);
	game.play();

	delete dt;
	delete mark;
	return 0;
}