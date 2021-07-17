#pragma once
#include "Livings.h"
#include "HeroesTeam.h"
#include <list>
using namespace std;

class Database {
	list<Warrior*> warriors;
	list<Sorcerer*> sorcerers;
	list<Paladin*> paladins;

	list<Dragon*> dragons;
	list<Exoskeleton*> exoskeletons;
	list<Spirit*> spirits;

	HeroesTeam* team;

	void insertWarrior(const string name, const int magicPower, const int strength, const int dexterity, const int agility);
	void insertSorcerer(const string name, const int magicPower, const int strength, const int dexterity, const int agility);
	void insertPaladin(const string name, const int magicPower, const int strength, const int dexterity, const int agility);

	void insertDragon(const string name, const int level, const int damageRate, const int defence, const int agility);
	void insertExoskeleton(const string name, const int level, const int damageRate, const int defence, const int agility);
	void insertSpirit(const string name, const int level, const int damageRate, const int defence, const int agility);

	void chooseYourTeam();
	Hero* validHeroName(string h_name);
  public:
	Database();						// calls the inserts - pushes livings in each list
	~Database();					// deletes+removes everything from each list
	void effects(string effect);	// printing some effects when heroes/monsters win - or basic info when starting the game
	HeroesTeam* get_myHeroesTeam();
	list <Monster*> monsterGenerator();
};