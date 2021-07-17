#pragma once
#include <string>
using namespace std;

class Item;
class Weapon;
class Armor;
class Potion;

/******************************** Item ********************************/
class Item {
  protected:
	string name;
	int cost;
	int minLevel;
    bool used; 		//flag if the item is available during the round of the fight (true: available, false:unavailable)
  public:
	Item(const string name, const int cost, const int level);
	virtual ~Item();
	string get_name();
	int get_cost();
	int get_minLevel();
    bool get_used();
    void set_used(bool state);
	virtual string get_item_kind() = 0;			// if we have a pointer to the mother.
	virtual int get_damage();					// functions of the derived classes
	virtual int get_handsNeeded();
	virtual int get_defence();
	virtual int get_IncreaseTrait();
	virtual void set_damage(int strength);		// for when a hero picks a weapon(equips)
	virtual string get_type();
};

/******************************** Weapon ********************************/
class Weapon : public Item {
	int damage;
	int handsNeeded;   // 1 or 2
  public:
	Weapon(const string name, const int cost, const int level, const int damage, const int handsNeed);
	~Weapon();
	int get_damage();
	int get_handsNeeded();
	string get_item_kind();
	void set_damage(int strength);	// for when a hero picks a weapon(equips)
};

/******************************** Armor ********************************/
class Armor : public Item {
	int defence;					// reduction of the damage an opponent will do
    int handsNeeded;				// 1
  public:
	Armor(const string name, const int cost, const int level, const int defence);
	~Armor();
	int get_defence();
    int get_handsNeeded();
	string get_item_kind();
};

/******************************** Potion ********************************/
class Potion : public Item {
	int increaseTrait;
	string type;		// which hero's trait is increased, depends on the type of potion
  public:
	Potion(const string name, const int cost, const int level, const int incrTrait, const string type);
    ~Potion();
	int get_IncreaseTrait();
	string get_item_kind();
	string get_type();
};