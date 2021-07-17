#pragma once
#include "Items.h"
#include "Spells.h"
#include "HeroesTeam.h"
#include <list>
using namespace std;

class Market {
	list<Weapon*> weapons;
	list<Armor*> armors;
	list<Potion*> potions;

	list<IceSpell*> iceSpells;
	list<FireSpell*> fireSpells;
	list<LightingSpell*> lightingSpells;

	void insertWeapon(const string name, const int cost, const int minLevel, const int damage, const int handsNeeded);
	void insertArmor(const string name, const int cost, const int minLevel, const int defence);
	void insertPotion(const string name, const int cost, const int minLevel, const int increaseTrait, const string type);

	void insertIceSpell(const string name, const int price, const int level, const int damageRate, const int minMagPower, const int decrDamageRate);
	void insertFireSpell(const string name, const int price, const int level, const int damageRate, const int minMagPower, const int decrDefence);
	void insertLightingSpell(const string name, const int price, const int level, const int damageRate, const int minMagPower, const int decrAgility);
  public:
	Market();
	~Market();
	void visit(HeroesTeam* myTeam);
	void print_items();
	void print_spells();
	Item* validItem(const string product);
	Spell* validSpell(const string product);
	bool checkTransaction(Hero* member, Item* item);
	bool checkTransaction(Hero* member, Spell* spell);
}; 