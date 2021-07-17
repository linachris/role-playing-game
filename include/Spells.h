#pragma once
#include <string>
using namespace std;

class Spell {
  protected:
    string name;
    int cost;
    int minLevel; 	 //number of level the Hero must be to use the spell
    int damageRange; //from 0 to damage_range, depends on the Heros dexterity
    int minMagPower; //least amount of magicPower required to be used
  public:
    Spell(const string name, const int price, const int level, const int damageRange, const int magic_energy);
    virtual ~Spell();
    string get_name();
    int get_cost();
    int get_minLevel();
    int get_damageRange();
    int get_minMagPower();
	virtual string get_spell_type() = 0;
	virtual int get_decrDamageRate();	// if we have a pointer to the mother.
	virtual int get_decrDefence();
	virtual int get_decrAgility();
};

/******************************** IceSpell ********************************/
class IceSpell: public Spell {
    int decrDamageRate;                // decreases monster's damage range
public:
    IceSpell(const string name, const int price, const int level, const int damage_rate, const int magic_energy, const int decrDamageRate);
    ~IceSpell();
	int get_decrDamageRate();
    string get_spell_type();
};


/******************************** FireSpell ********************************/
class FireSpell: public Spell {
    int decrDefence;                // decreases monster's defence rate
public:
    FireSpell(const string name, const int price, const int level, const int damage_rate, const int magic_energy, const int decrDefence);
    ~FireSpell();
	int get_decrDefence();
    string get_spell_type();
};


/******************************** LightingSpell ********************************/
class LightingSpell: public Spell {
    int decrAgility;                // decreases monster's agility
public:
    LightingSpell(const string name, const int price, const int level, const int damage_rate, const int magic_energy, const int decrAgility);
    ~LightingSpell();
	int get_decrAgility();
    string get_spell_type();
};