#pragma once
#include <string>
#include "Database.h"
#include "Market.h"
#include "Livings.h"
#include "Items.h"
#include "HeroesTeam.h"
#include "CommDefines.h"

#define LENGTH 7
#define WIDTH 7

class Grid {
	char** map;
	Market* gameMarket;				// for items and spells
	Database* livings; 				// for heroes and monsters && my HeroesTeam!
  public:
	Grid(Market*, Database*);
	Grid() {}
	~Grid();

	bool move();
	bool move_up();
	bool move_down();
	bool move_right();
	bool move_left();
    Location* get_TeamLocation();
	void displayMap();
	void examineArea();

	void checkPointMenu();
	void checkPointRound();

	void fight();
	void attack(Hero* hero, Monster* monster);
	void castSpell(Hero* hero, Monster* monster);
	void monster_attack(Hero* hero, Monster* monster);

    HeroesTeam* get_MyTeam();
	int HeroesHealth(list <Hero*> myHeroes, int);
	int MonstersHealth(list <Monster*> monsters_choosen, int);
    void displayTeamStats();
	void displayMonStats(list <Monster*> monsters_choosen);

	void play();
};