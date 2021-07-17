#pragma once
#include <string>
#include <list>
#include "Items.h"
#include "Spells.h"
#include "CommDefines.h"
using namespace std;

class Living;

class Hero;
class Warrior;
class Sorcerer;
class Paladin;

class Monster;
class Dragon;
class Exoskeleton;
class Spirit;

class Living {
  protected:
	string name;
	int level;
	int healthPower;
  public:
	Living(const string name,const int level);
	virtual ~Living();
	string get_name();
	int get_level();
	int get_healthPower();
    void set_healthPower(int);
	void incr_healthPower(int);
	void decr_healthPower(int);
	bool has_fainted();
};

///////////////////////////////// HEROES /////////////////////////////////
class Hero : public Living {
  protected:
	int magicPower;
	int strength;	// incr at levelup
	int dexterity;	// incr at levelup
	int agility;	// incr at levelup
	int money;
	int experience;
    int hands_occupied;
	list<Item*> Items;		// the items the hero owns
	list<Spell*> Spells;	// the spells the hero owns
  public:
	Hero(const string name, const int magicPower, const int strength, const int dexterity, const int agility);
	virtual ~Hero();

	int get_magicPower();
	int get_strength();
	int get_dexterity();
	int get_agility();
	int get_money();
	int get_experience();

	void incr_magicPower(int magicPower);
	void incr_strength(int strength);
	void incr_dexterity(int dexterity);
	void incr_agility(int agility);
	void incr_money(int money);
	void incr_experience(int experience);
    void decr_magicPower(int decrease);

	virtual void levelUp() = 0;				// each hero's trait is affected differently
	virtual string get_hero_type() = 0;

	void buy(Item*);
	void buy(Spell*);
	void sell(Item*);
	void sell(Spell*);
	void checkInventoryMenu();
	bool checkInventory(string choice);

	list<Item*> get_Items();
	list<Spell*> get_Spells();
	Item* validItemName(string i_name); 	// armor or weapon
	Item* validPotionName(string p_name);
    Spell* validSpellName(string s_name);
	Item* equip();
	void use();
    void free_hands();
    bool holds_Armor();
};

/******************************** Warrior ********************************/
class Warrior : public Hero {
  public:
	Warrior(const string name, const int magicPower, const int strength, const int dexterity, const int agility);
	~Warrior();
	void levelUp();
	string get_hero_type();
};

/******************************** Sorcerer ********************************/
class Sorcerer : public Hero {
  public:
	Sorcerer(const string name, const int magicPower, const int strength, const int dexterity, const int agility);
	~Sorcerer();
	void levelUp();
	string get_hero_type();
};

/******************************** Paladin ********************************/
class Paladin : public Hero {
  public:
	Paladin(const string name, const int magicPower, const int strength, const int dexterity, const int agility);
	~Paladin();
	void levelUp();
	string get_hero_type();
};

///////////////////////////////// MONSTERS /////////////////////////////////
class Monster : public Living {
  protected:
	int damageRate; //from 0 to damage_range
	int defence;
	int agility;
  public:
	Monster(const string name, const int level, const int damageRate, const int defence, const int agility);
	virtual ~Monster();
    int get_damageRate();
    int get_defence();
    int get_agility();
    void set_defence(int decrease);
    void set_damageRate(int decrease);
    void set_agility(int decrease);
};

/******************************** Dragon ********************************/
class Dragon : public Monster {
  public:
	Dragon(const string name, const int level, const int damageRate, const int defence, const int agility);
	~Dragon();
};

/******************************** Exoskeleton ********************************/
class Exoskeleton : public Monster {
  public:
	Exoskeleton(const string name, const int level, const int damageRate, const int defence, const int agility);
	~Exoskeleton();
};

/******************************** Spirit ********************************/
class Spirit : public Monster {
  public:
	Spirit(const string name, const int level, const int damageRate, const int defence, const int agility);
	~Spirit();
};