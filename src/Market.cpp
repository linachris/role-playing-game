#include "Market.h"
#include <fstream>
#include <iostream>

// initializing the market, with Items and Spells from txt files
Market::Market() {
	string name, type;
	int cost, minLevel, damage, handsNeeded, defence, increaseTrait;
	int price, damageRate, minMagPower, decr;

	/************************* Weapons *************************/
	ifstream Weapons("txt/Weapons.txt");
	if (!Weapons) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while (Weapons >> name >> cost >> minLevel >> damage >> handsNeeded)
		insertWeapon(name, cost, minLevel, damage, handsNeeded);

	/************************* Armors *************************/
	ifstream Armors("txt/Armors.txt");
	if (!Armors) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while (Armors >> name >> cost >> minLevel >> defence)
		insertArmor(name, cost, minLevel, defence);

	/************************* Potions *************************/
	ifstream Potions("txt/Potions.txt");
	if (!Potions) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while (Potions >> name >> cost >> minLevel >> increaseTrait >> type)
		insertPotion(name, cost, minLevel, increaseTrait, type);

	/************************* IceSpells *************************/
	ifstream IceSpells("txt/IceSpells.txt");
	if (!IceSpells) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while (IceSpells >> name >> price >> minLevel >> damageRate >> minMagPower >> decr)
		insertIceSpell(name, price, minLevel, damageRate, minMagPower, decr);

	/************************* FireSpells *************************/
	ifstream FireSpells("txt/FireSpells.txt");
	if (!FireSpells) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while (FireSpells >> name >> price >> minLevel >> damageRate >> minMagPower >> decr)
		insertFireSpell(name, price, minLevel, damageRate, minMagPower, decr);

	/************************* LightingSpells *************************/
	ifstream LightingSpells("txt/LightingSpells.txt");
	if (!LightingSpells) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while (LightingSpells >> name >> price >> minLevel >> damageRate >> minMagPower >> decr)
		insertLightingSpell(name, price, minLevel, damageRate, minMagPower, decr);
}

Market::~Market() {
	while (!lightingSpells.empty()) {
		delete lightingSpells.back();
		lightingSpells.pop_back();
	}
	while (!fireSpells.empty()) {
		delete fireSpells.back();
		fireSpells.pop_back();
	}
	while (!iceSpells.empty()) {
		delete iceSpells.back();
		iceSpells.pop_back();
	}
	while (!potions.empty()) {
		delete potions.back();
		potions.pop_back();
	}
	while (!armors.empty()) {
		delete armors.back();
		armors.pop_back();
	}
	while (!weapons.empty()) {
		delete weapons.back();
		weapons.pop_back();
	}
}

void Market::insertWeapon(const string name, const int cost, const int minLevel, const int damage, const int handsNeeded) {
	Weapon* toAdd = new Weapon(name, cost, minLevel, damage, handsNeeded);
	weapons.push_back(toAdd);
}

void Market::insertArmor(const string name, const int cost, const int minLevel, const int defence) {
	Armor* toAdd = new Armor(name, cost, minLevel, defence);
	armors.push_back(toAdd);
}

void Market::insertPotion(const string name, const int cost, const int minLevel, const int increaseTrait, const string type) {
	Potion* toAdd = new Potion(name, cost, minLevel, increaseTrait, type);
	potions.push_back(toAdd);
}

void Market::insertIceSpell(const string name, const int price, const int level, const int damageRate, const int minMagPower, const int decrDamageRate) {
	IceSpell* toAdd = new IceSpell(name, price, level, damageRate, minMagPower, decrDamageRate);
	iceSpells.push_back(toAdd);
}

void Market::insertFireSpell(const string name, const int price, const int level, const int damageRate, const int minMagPower, const int decrDefence) {
	FireSpell* toAdd = new FireSpell(name, price, level, damageRate, minMagPower, decrDefence);
	fireSpells.push_back(toAdd);
}

void Market::insertLightingSpell(const string name, const int price, const int level, const int damageRate, const int minMagPower, const int decrAgility) {
	LightingSpell* toAdd = new LightingSpell(name, price, level, damageRate, minMagPower, decrAgility);
	lightingSpells.push_back(toAdd);
}

void Market::print_items() {
	cout << BGREEN << "Welcome to the Items market! " << RESTORE << endl;
	cout << "Here's the Items; menu: \n\n";
	cout << "================================ Available Weapons ==================================\n";
	cout << " Name\t\t" << "        Cost\t\t" << "\b\bmin Level\t\t" << "Damage\t" << "    Hands Needed\t\t" << endl;
	cout << "-------------------------------------------------------------------------------------\n";
	for(list<Weapon*>::iterator it = weapons.begin(); it!= weapons.end(); ++it)
	{
		cout << (*it)->get_name() << "\t\t" << (*it)->get_cost()
		<< "\t\t" << (*it)->get_minLevel() << " \t\t " << (*it)->get_damage()
		<< "\t\t " << (*it)->get_handsNeeded() << "\t\n";
	}
	cout << endl;

	cout << "================================= Available Armor ===================================\n";
	cout << " Name\t\t" << "        Cost\t\t" << "\b\bmin Level\t\t" << "Defence\t\t" << endl;
	cout << "-------------------------------------------------------------------------------------\n";
	for(list<Armor*>::iterator it = armors.begin(); it!= armors.end(); ++it)
	{
		cout << (*it)->get_name() << "\t\t" << (*it)->get_cost()
		<< "\t\t" << (*it)->get_minLevel() << "\t\t" << (*it)->get_defence() << "\t\n";
	}
	cout << endl;

	cout << "================================= Available Potions ===================================\n";
	cout << " Name\t\t" << "        Cost\t\t" << "\b\bmin Level\t\t" << "Benefits\t\t" << endl;
	cout << "---------------------------------------------------------------------------------------\n";
	for(list<Potion*>::iterator it = potions.begin(); it!= potions.end(); ++it)
	{
		cout << (*it)->get_name() << "\t\t" << (*it)->get_cost()
		<< "\t\t" << (*it)->get_minLevel() << "\t\t" << (*it)->get_type()  << "\t\n";
	}
	cout << endl;
}

void Market::print_spells() {
	cout << BGREEN << "Welcome to the Spells market! " << RESTORE << endl;
	cout << "Here's the Spells' menu: \n\n";
	cout << "================================= Available IceSpells ===================================\n";
	cout << " Name\t\t" << "        Cost\t\t" << "\b\bmin Level\t" << "    Damage Range  " << "Magic Power Required\t\t" << endl;
	cout << "-----------------------------------------------------------------------------------------\n";
	for(list<IceSpell*>::iterator it = iceSpells.begin(); it!= iceSpells.end(); ++it)
	{
		cout << (*it)->get_name() << "\t\t" << (*it)->get_cost()
		<< "\t\t" << (*it)->get_minLevel() << " \t\t " << (*it)->get_damageRange()
		<< "\t\t " << (*it)->get_minMagPower() << "\t\n";
	}
	cout << endl;

	cout << "================================= Available FireSpells ===================================\n";
	cout << " Name\t\t" << "        Cost\t\t" << "\b\bmin Level\t" << "    Damage Range  " << "Magic Power Required\t\t" << endl;
	cout << "------------------------------------------------------------------------------------------\n";
	for(list<FireSpell*>::iterator it = fireSpells.begin(); it!= fireSpells.end(); ++it)
	{
		cout << (*it)->get_name() << "\t\t" << (*it)->get_cost()
		<< "\t\t" << (*it)->get_minLevel() << " \t\t " << (*it)->get_damageRange()
		<< "\t\t " << (*it)->get_minMagPower() << "\t\n";
	}
	cout << endl;

	cout << "================================= Available LightingSpells ===================================\n";
	cout << " Name\t\t" << "        Cost\t\t" << "\b\bmin Level\t" << "    Damage Range  " << "Magic Power Required\t\t" << endl;
	cout << "----------------------------------------------------------------------------------------------\n";
	for(list<LightingSpell*>::iterator it = lightingSpells.begin(); it!= lightingSpells.end(); ++it)
	{
		cout << (*it)->get_name() << "\t\t" << (*it)->get_cost()
		<< "\t\t" << (*it)->get_minLevel() << " \t\t " << (*it)->get_damageRange()
		<< "\t\t " << (*it)->get_minMagPower() << "\t\n";
	}
	cout << endl;
}

void Market::visit(HeroesTeam* myTeam) {
	cout << endl << endl << endl;
	cout << BGREEN << "!!!!!!!!  You entered the market universe !!!!!!!!" << RESTORE << endl;

	while(1) {
		//       CHOOSING TO BUY OR SELL
		cout << "Would you like to buy or sell something? (Type \"buy\" or \"sell\"): ";
		string answer;
		cin >> answer;
		while ((answer != "buy") && (answer != "sell")) {
			cout << "Expected \"buy\" or \"sell\", please try again: ";
			cin >> answer;
		}

		if(answer == "buy" ) cout << BACKROUNDCYAN << "Which member of your team would like to buy something? " << RESTORE << endl;
		if(answer == "sell") cout << BACKROUNDCYAN << "Which member of your team would like to sell something? " << RESTORE << endl;
		cout << BRED << "Reminder: " << RESTORE << " Your team members are: " << endl;
		myTeam->printHeroes(); 							//printing the names of the heroes
		cout << "Give a hero: ";
		Hero* member = myTeam->pickHeroFromTeam();		//the player picks a hero from the team

		///////////////////////////////////////////////////
		if(answer == "buy") {
			print_items();
			print_spells();

			//  CHOOSING ITEM OR SPELL PURCHASE
			cout << "Please select the category: (Type \"Item\" or \"Spell\"):";
			string choice;
			cin >> choice;
			while ((choice != "Item") && (choice != "Spell")) {
				cout << "Expected \"Item\" or \"Spell\", please try again: ";
				cin >> choice;
			}

			string product;
			if(choice == "Item") {
				//    CHOOSING A PARTICULAR ITEM
				cout << "Please select the name of the item, ";
				Item* itemToAdd;
				while(1) {
					cout << "Press \"q\" if you want to quit: ";
					cin >> product;
					if(product == "q") break;
					if((itemToAdd = validItem(product)) == NULL) {
						cout << "No Item exists with that name, please try again: ";
						continue;
					}
					if(checkTransaction(member, itemToAdd) == false) {
						cout << RED << "Your hero can't buy that..Please select another item!" << RESTORE << endl;
						continue;
					}

					if(itemToAdd->get_item_kind() == "Weapon") {
						Item* copiedItem = new Weapon(itemToAdd->get_name(), itemToAdd->get_cost(), itemToAdd->get_minLevel(), itemToAdd->get_damage(), itemToAdd->get_handsNeeded());
						member->buy(copiedItem);
					}
					else if(itemToAdd->get_item_kind() == "Armor") {
						Item* copiedItem = new Armor(itemToAdd->get_name(), itemToAdd->get_cost(), itemToAdd->get_minLevel(), itemToAdd->get_defence());
						member->buy(copiedItem);
					}
					else if(itemToAdd->get_item_kind() == "Potion") {
						Item* copiedItem = new Potion(itemToAdd->get_name(), itemToAdd->get_cost(), itemToAdd->get_minLevel(), itemToAdd->get_IncreaseTrait(), itemToAdd->get_type());
						member->buy(copiedItem);
					}
					break;
				}
			}
			else if(choice == "Spell") {
				//    CHOOSING A PARTICULAR SPELL
				cout << "Please select your spell, ";
				Spell* spellToAdd;
				while(1) {
					cout << "Press \"q\" if you want to quit: ";
					cin >> product;
					if(product == "q") break;
					if((spellToAdd = validSpell(product)) == NULL) {
						cout << "No Spell exists with that name, please try again: ";
						continue;
					}
					if(checkTransaction(member, spellToAdd) == false) {
						cout << RED << "Your hero can't buy that..Please select another spell!" << RESTORE << endl;
						continue;
					}
					Spell* spellBought;
					if (spellToAdd->get_spell_type() == "IceSpell")
						spellBought = new IceSpell(spellToAdd->get_name(), spellToAdd->get_cost(), spellToAdd->get_minLevel(), spellToAdd->get_damageRange(), spellToAdd->get_minMagPower(), spellToAdd->get_decrDamageRate());
					if (spellToAdd->get_spell_type() == "FireSpell")
						spellBought = new FireSpell(spellToAdd->get_name(), spellToAdd->get_cost(), spellToAdd->get_minLevel(), spellToAdd->get_damageRange(), spellToAdd->get_minMagPower(), spellToAdd->get_decrDefence());
					if (spellToAdd->get_spell_type() == "LightingSpell")
						spellBought = new LightingSpell(spellToAdd->get_name(), spellToAdd->get_cost(), spellToAdd->get_minLevel(), spellToAdd->get_damageRange(), spellToAdd->get_minMagPower(), spellToAdd->get_decrAgility());
					member->buy(spellBought);
					break;
				}
			}
		}
		///////////////////////////////////////////////////
		else if(answer == "sell") {
			//  CHOOSING ITEM OR SPELL TO SELL
			cout << "Please select the category: (Type \"items\" or \"spells\"):";
			string choice;
			cin >> choice;
			while ((choice != "items") && (choice != "spells")) {
				cout << "Expected \"items\" or \"spells\", please try again: ";
				cin >> choice;
			}

			if(member->checkInventory(choice)) {
				string product;
				if(choice == "items") {
					cout << "Please select the name of the item, ";
					Item* itemToRem;
					while(1) {
						cout << "Press \"q\" if you want to quit: ";
						cin >> product;
						if(product == "q") break;
						if((itemToRem = validItem(product)) == NULL) {
							cout << "No Item exists with that name, please try again: ";
							continue;
						}
						member->sell(itemToRem);
						break;
					}
				}
				else if(choice == "spells") {
					//    CHOOSING A PARTICULAR SPELL
					cout << "Please select your spell, ";
					Spell* spellToRem;
					while(1) {
						cout << "Press \"q\" if you want to quit: ";
						cin >> product;
						if(product == "q") break;
						if((spellToRem = validSpell(product)) == NULL) {
							cout << "No Spell exists with that name, please try again: ";
							continue;
						}
						member->sell(spellToRem);
						break;
					}
				}
			}
		}
		///////////////////////////////////////////////////
		string rep;
		cout << "Would you like to make another purchase? (Type \"yes\" or \"no\"):";
		cin >> rep;
		while ((rep != "yes") && (rep != "no")) {
			cout << "Expected \"yes\" or \"no\", please try again: ";
			cin >> rep;
		}
		if(rep == "no") break;
	}
}

bool Market::checkTransaction(Hero* member, Item* item) {
	if((member->get_money() >= item->get_cost()) && (member->get_level() >= item->get_minLevel()))
	{
		cout << CYAN << member->get_name() << " purchased a " << item->get_name() << RESTORE << endl;
		return true;
	}
	return false;
}

bool Market::checkTransaction(Hero* member, Spell* spell) {
	if((member->get_money() >= spell->get_cost()) && (member->get_level() >= spell->get_minLevel()) && (member->get_magicPower() >= spell->get_minMagPower())) {
		cout << CYAN << member->get_name() << " purchased a " << spell->get_name() << RESTORE << endl;
		return true;
	}
	return false;
}

// returns NULL if no item exists with that name - the item is returned otherwise
Item* Market::validItem(const string product) {
	for (list<Weapon*>::iterator it = weapons.begin(); it != weapons.end(); ++it)
		if ((*it)->get_name() == product)
			return *it;

	for (list<Armor*>::iterator it = armors.begin(); it != armors.end(); ++it)
		if ((*it)->get_name() == product)
			return *it;

	for (list<Potion*>::iterator it = potions.begin(); it != potions.end(); ++it)
		if ((*it)->get_name() == product)
			return *it;
	return NULL;
}

// returns NULL if no spell exists with that name - the spell is returned otherwise
Spell* Market::validSpell(const string product) {
	for (list<IceSpell*>::iterator it = iceSpells.begin(); it != iceSpells.end(); ++it)
		if ((*it)->get_name() == product)
			return *it;

	for (list<FireSpell*>::iterator it = fireSpells.begin(); it != fireSpells.end(); ++it)
		if ((*it)->get_name() == product)
			return *it;

	for (list<LightingSpell*>::iterator it = lightingSpells.begin(); it != lightingSpells.end(); ++it)
		if ((*it)->get_name() == product)
			return *it;
	return NULL;
}