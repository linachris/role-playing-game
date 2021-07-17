#include "Livings.h"
#include <iostream>
using namespace std;

/******************************** Living ********************************/
Living::Living(const string name,const int level=1)
: name(name), level(level), healthPower(400) {}

string Living::get_name() { return name; }

int Living::get_level() { return level; }

int Living::get_healthPower() { return healthPower; }

void Living::set_healthPower(int hP) { healthPower = hP; }

void Living::incr_healthPower(int hlthPower) { healthPower += hlthPower; }

void Living::decr_healthPower(int decrease) {
	healthPower -= decrease;
	if(healthPower < 0) healthPower=0;
}

bool Living::has_fainted() { return (healthPower <= 0); }

Living::~Living() {}

/******************************** Warrior ********************************/
Hero::Hero(const string name, const int magicPower, const int strength, const int dexterity, const int agility)
: Living(name), magicPower(magicPower), strength(strength), dexterity(dexterity), agility(agility), money(800), experience(140),hands_occupied(0) {}

Hero::~Hero() {}

int Hero::get_magicPower() { return magicPower; }

int Hero::get_strength() {return strength; }

int Hero::get_dexterity() { return dexterity; }

int Hero::get_agility() { return agility; }

int Hero::get_money() {return money; }

int Hero::get_experience() { return experience; }

void Hero::incr_magicPower(int magPower) { magicPower += magPower; }

void Hero::incr_strength(int str) { strength += str; }

void Hero::incr_dexterity(int dext) { dexterity += dext; }

void Hero::incr_agility(int agil) { agility += agil; }

void Hero::incr_money(int mon) { money += mon; }

void Hero::incr_experience(int exp) { experience += exp; }

void Hero::decr_magicPower(int decrease) {
	magicPower-= decrease;
	if(magicPower < 0) magicPower=0;
}

//returns true:hero holds armor, false:hero doesn't hold armor
bool Hero::holds_Armor() {
	for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
		if((*it)->get_used() == false && (*it)->get_item_kind() == "Armor")
			return true;
	return false;
}

void Hero::buy(Item* item) {
	money -= item->get_cost();
	if (money < 0)
		money = 0;
	Items.push_back(item);
}

void Hero::buy(Spell* spell) {
	money -= spell->get_cost();
	if (money < 0) 
		money = 0;
	Spells.push_back(spell);
}

void Hero::sell(Item* item) {
	money += item->get_cost()/2;
	for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it) {
		if ((*it)->get_name() == item->get_name()) {
			delete (*it);
			Items.erase(it);
			cout << CYAN << "Item sold!" << RESTORE << endl;
			return;
		}
	}
	cout << "There is no such item in your inventory!\n";
}

void Hero::sell(Spell* spell) {
	money += spell->get_cost()/2;
	for (list<Spell*>::iterator it = Spells.begin(); it != Spells.end(); ++it) {
		if ((*it)->get_name() == spell->get_name()) {
			delete (*it);
			Spells.erase(it);
			cout << CYAN << "Spell sold!" << RESTORE << endl;
			return;
		}
	}
	cout << "There is no such spell in your inventory!\n";
}

list<Item*> Hero::get_Items() { return Items; }

list<Spell*> Hero::get_Spells() { return Spells; }

void Hero::checkInventoryMenu() {
	cout << endl;
	cout << BLK << "<<<=====>>>  <<<====>>>  <<<====>>>  YOUR INVENTORY  <<<=====>>>  <<<====>>>  <<<====>>>" << RESTORE << endl;
	checkInventory("items");
	checkInventory("spells");
	cout << BLK << "<<<=====>>>   <<<====>>>   <<<====>>>  <<<====>>>   <<<=====>>>   <<<====>>>  <<<====>>>" << RESTORE << endl;
}

// returns false if whatever the choice is, the Hero's list of that choice is empty 
bool Hero::checkInventory(string choice) {

	if (choice == "items") {
		if (Items.size() == 0) {
			cout << IWHITE << "You have no Items in your inventory! Visit a Market to buy some!" << RESTORE << endl;
			return false;
		}
		cout << BYELL << "==================================== Hero's Items ======================================" << RESTORE << endl;
		cout << "Name\t\t" << "Item's Kind\t" << "Cost\t" << "Damage\t" << "  HandsNedeed\t" << " Defence\t" << "Benefits\t" << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		for(list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it) {
			if ((*it)->get_item_kind() == "Weapon")
				cout << (*it)->get_name() << "\t  " << (*it)->get_item_kind() << "\t" << (*it)->get_cost()
				<< "\t " << (*it)->get_damage() << "\t\t" << (*it)->get_handsNeeded()
				<< "\t    X\t\t   X\n";

			else if ((*it)->get_item_kind() == "Armor")
				cout << (*it)->get_name() << "\t  " << (*it)->get_item_kind() << "\t\t" << (*it)->get_cost()
				<< "\t  X\t\t" << (*it)->get_handsNeeded() << "\t  " << (*it)->get_defence()
				<< "\t\t   X\n";

			else if ((*it)->get_item_kind() == "Potion")
				cout << (*it)->get_name() << "\t  " << (*it)->get_item_kind() << "\t" << (*it)->get_cost()
				<< "\t  X\t\tX\t    X\t\t  " << (*it)->get_type() << endl;
		}
		cout << endl;
	}
	// this option only during a checkpoint!
	else if ((choice == "weapons") || (choice == "armors")) {
		bool noWepArm = true;
		if (Items.size() == 0) {
			cout << IWHITE << "You have no Weapons/Armors in your inventory! Visit a Market to buy some!" << RESTORE << endl;
			return false;
		}
		cout << BYELL << "================================= Hero's Weapons/Armors ===================================" << RESTORE << endl;
		cout << "Name\t\t" << "Item's Kind\t" << "Cost\t" << "Damage\t" << "  HandsNedeed\t" << " Defence\t" << endl;
		cout << "----------------------------------------------------------------------------------------\n";
		for(list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it) {
			if ((*it)->get_item_kind() == "Weapon") {
				cout << IWHITE << (*it)->get_name() << RESTORE << "\t  " << (*it)->get_item_kind() << "\t" << (*it)->get_cost()
				<< "\t " << (*it)->get_damage() << "\t\t" << (*it)->get_handsNeeded()
				<< "\t    X\n";
				noWepArm = false;
			}
			else if ((*it)->get_item_kind() == "Armor") {
				cout << (*it)->get_name() << "\t  " << (*it)->get_item_kind() << "\t\t" << (*it)->get_cost()
				<< "\t  X\t\t" << (*it)->get_handsNeeded() << "\t  " << (*it)->get_defence() << endl;
				noWepArm = false;
			}
		}
		if (noWepArm) {
			cout << IWHITE << "You have no Weapons/Armors in your inventory, to equip! Visit a Market to buy some!" << RESTORE << endl;
			return false;
		}
		else
			cout << IYELL << "Choose a Weapon/Armor to equip:" << RESTORE;
		cout << endl;
	}

	else if (choice == "potions") {
		bool noPotions = true;
		if (Items.size() == 0) {
			cout << IWHITE << "You have no Potions in your inventory, to use! Visit a Market to buy some!" << RESTORE << endl;
			return false;
		}
		for(list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
			if ((*it)->get_item_kind() == "Potion")
				noPotions = false;

		if (noPotions) {
			cout << IWHITE << "You have no Potions in your inventory, to use! Visit a Market to buy some!" << RESTORE << endl;
			return false;
		}
		else {
			cout << BYELL << "================================= Hero's Potions ===================================" << RESTORE << endl;
			cout << "Name\t\t" << "Item's Kind\t" << "Cost\t" << "Benefits\t" << endl;
			cout << "----------------------------------------------------------------------------------------\n";
			for(list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
				if ((*it)->get_item_kind() == "Potion")
					cout << (*it)->get_name() << "\t  " << (*it)->get_item_kind() << "\t" << (*it)->get_cost()
					<< "\t  " << (*it)->get_type() << endl;

			cout << IYELL << "Choose a Potion to use:" << RESTORE;
		}
		cout << endl;
	}

	else if (choice == "spells") {
		if (Spells.size() == 0) {
			cout << IWHITE << "You have no Spells in your inventory! Visit a Market to buy some!" << RESTORE << endl;
			return false;
		}
		cout << BYELL << "=============================== Hero's Spells ===============================" << RESTORE << endl;
		cout << "Name\t\t" << "SpellType\t\t" << "Cost\t" << "DamageRange\t" << "minMagicPower" << endl;
		cout << "-----------------------------------------------------------------------------\n";
		for(list<Spell*>::iterator it = Spells.begin(); it != Spells.end(); ++it) {
			cout << (*it)->get_name() << "\t " << (*it)->get_spell_type() << "\t\t" << (*it)->get_cost()
			<< "\t  " << (*it)->get_damageRange() << "\t\t    " << (*it)->get_minMagPower() << endl;
		}
	}
	return true;
}

/******************************** fight functions ********************************/
// returns NULL is there is no Weapon/Armor to equip == or the Weapon/Armor the Hero owns
Item* Hero::equip() {
	Item* itToEquip = NULL;				// returns NULL is there is no Weapon/Armor to equip
	if (checkInventory("weapons")) {	// this will show both weapons and armors!
		while(1) {
			string toequip;
			cout << "\nGive the name of the Item(Weapon or Armor) you want to use or type \"quit\":";
			cin >> toequip;
			while (1) {
				if (toequip == "quit") 
					break;
				if((itToEquip = validItemName(toequip)) == NULL)
					cout << RED << "No Item with that name exists in your inventory, please try again(or type \"quit\"): " << RESTORE;
				else if(((itToEquip->get_handsNeeded() == 2) && (hands_occupied != 0)) || ((itToEquip->get_handsNeeded() == 1) && (hands_occupied == 2)))
					cout << RED << "You don't have enough free hands for this item. Please select a different one(or type \"quit\"):" << RESTORE;
			    else if(itToEquip->get_used() == false) //the current item is being used so you can't re-use it for now
					cout << RED << "The current item is being used so you can't re-use it for now. Please select a different one(or type \"quit\"):" << RESTORE;
				else
					break;
				cin >> toequip;
			}
			if (toequip == "quit") 
				break;

			if (itToEquip->get_item_kind() == "Weapon")
				itToEquip->set_damage(strength);				// hero's strength is added to the damage a weapon can cause		
			else		
				incr_agility(itToEquip->get_defence());			// the armor's defence rate -> increases hero's agility
			
			cout << BACKROUNDCYAN << "Your hero just equipped " << itToEquip->get_name() << " !!" << RESTORE << endl;
			hands_occupied += itToEquip->get_handsNeeded();
			itToEquip->set_used(false); //setting the current item as being used so you can't re-use it for now
			cout << endl;
		}
	}
	return itToEquip;
}

// returns NULL if no Item exists with that i_name - else the Item is returned if exists
Item* Hero::validItemName(string i_name) {
	int counter=0;
	for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
		if ((*it)->get_name() == i_name)
			counter++;
	for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it) {
		if ((*it)->get_name() == i_name) {	
			if(counter > 1)(*it)->set_used(true);	//if one item's quantity is more than 1
			return *it;
		}
	}
	return NULL;
}

void Hero::use() {
	if (checkInventory("potions")) {
		string touse;
		cout << "Please give the name of the potion you would like to use:";
		cin >> touse;
		Item* poToUse;
		while ((poToUse = validPotionName(touse)) == NULL) {
			cout << "No Potion with that name exists in your inventory, please try again: ";
			cin >> touse;
		}
		if (poToUse->get_type() == "health")
			incr_healthPower(poToUse->get_IncreaseTrait());
		else if (poToUse->get_type() == "magicPower")
			incr_magicPower(poToUse->get_IncreaseTrait());
		else if (poToUse->get_type() == "dexterity")
			incr_dexterity(poToUse->get_IncreaseTrait());
		else if (poToUse->get_type() == "agility")
			incr_agility(poToUse->get_IncreaseTrait());
		else if (poToUse->get_type() == "strength")
			incr_strength(poToUse->get_IncreaseTrait());
		else if (poToUse->get_type() == "all") {
			incr_healthPower(poToUse->get_IncreaseTrait());
			incr_magicPower(poToUse->get_IncreaseTrait());
			incr_dexterity(poToUse->get_IncreaseTrait());
			incr_agility(poToUse->get_IncreaseTrait());
			incr_strength(poToUse->get_IncreaseTrait());
		}
		for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
			if ((*it)->get_item_kind() == "Potion")
				if ((*it)->get_name() == touse) {
					Items.erase(it);
					break;
				}
		cout << endl;
	}
}

// returns NULL if no Potion exists with that s_name - else the Spell is returned if exists
Item* Hero::validPotionName(string p_name) {
	for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
		if ((*it)->get_item_kind() == "Potion")
			if ((*it)->get_name() == p_name)
				return *it;
	return NULL;
}

Spell* Hero::validSpellName(string s_name) {
	for (list<Spell*>::iterator it = Spells.begin(); it != Spells.end(); ++it)
		if ((*it)->get_name() == s_name)
			return *it;
	return NULL;
}

void Hero::free_hands() {
	hands_occupied = 0;
	for (list<Item*>::iterator it = Items.begin(); it != Items.end(); ++it)
		(*it)->set_used(true);
}

/******************************** Warrior ********************************/
Warrior::Warrior(const string name, const int magicPower, const int strength, const int dexterity, const int agility)
: Hero(name, magicPower, strength, dexterity, agility) {}

Warrior::~Warrior() {}

void Warrior::levelUp() {
	level++;
	incr_strength(W_STR);
	incr_dexterity(W_DEXT);
	incr_agility(W_AGIL);
}

string Warrior::get_hero_type() { return "Warrior"; }

/******************************** Sorcerer ********************************/
Sorcerer::Sorcerer(const string name, const int magicPower, const int strength, const int dexterity, const int agility)
: Hero(name, magicPower, strength, dexterity, agility) {}

Sorcerer::~Sorcerer() {}

void Sorcerer::levelUp() {
	level++;
	incr_strength(S_STR);
	incr_dexterity(S_DEXT);
	incr_agility(S_AGIL);
}

string Sorcerer::get_hero_type() { return "Sorcerer"; }

/******************************** Paladin ********************************/
Paladin::Paladin(const string name, const int magicPower, const int strength, const int dexterity, const int agility)
: Hero(name, magicPower, strength, dexterity, agility) {}

Paladin::~Paladin() {}

void Paladin::levelUp() {
	level++;
	incr_strength(P_STR);
	incr_dexterity(P_DEXT);
	incr_agility(P_AGIL);
}

string Paladin::get_hero_type() { return "Paladin"; }