#pragma once
#include "Livings.h"
#include "Location.h"
#include "CommDefines.h"
using namespace std;

class HeroesTeam {
  	list<Hero*> myHeroes;
	Location* location;
  public:
	HeroesTeam(list<Hero*> heroes_choosen);
	~HeroesTeam();
	void displayStats();
	Hero* pickHeroFromTeam();
	Hero* validHeroName(string h_name);
	list<Hero*> get_myHeroes();
	Location* get_location();
    void printHeroes();
};