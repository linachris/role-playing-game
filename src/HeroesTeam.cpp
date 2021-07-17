#include "HeroesTeam.h"
#include <iostream>
using namespace std;

// creates the Heroes' list from the given list(that the player chose)
HeroesTeam::HeroesTeam(list<Hero*> heroes_choosen) {
	location = new Location;
	for (list<Hero*>::iterator it = heroes_choosen.begin(); it != heroes_choosen.end(); ++it)
		myHeroes.push_back(*it);
}
// deletes the dynamically allocated memory for Items/Spells each Hero of the HeroesTeam
// owns, in case of not having sold them already, when quiting the game
HeroesTeam::~HeroesTeam() { 
	for (list<Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it) {
		list<Item*> heroItems = (*it)->get_Items();
		list<Spell*> heroSpells = (*it)->get_Spells();

		while(!heroItems.empty()) {
			delete heroItems.back();
			heroItems.pop_back();
		}
		while(!heroSpells.empty()) {
			delete heroSpells.back();
			heroSpells.pop_back();
		}
	}
	delete location; 
}

// displays the HeroesTeam's statistics
void HeroesTeam::displayStats() {
	cout << BYELL << "================================================ My Team's Stats ======================================================" << RESTORE << endl;
	cout << "Name\t\t" << "Level\t" << "HealthPower\t" << "Experience\t" << "Money\t  " << "MagicPower\t" << "Strength\t" << "Dexterity\t" << "Agility" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	for (list<Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it)
		cout << UWHITE << (*it)->get_name() << RESTORE << "\t  " << BWHITE << (*it)->get_level() << RESTORE << "\t   " << BWHITE << (*it)->get_healthPower() << RESTORE << "\t\t   "
		<< (*it)->get_experience() << "\t\t " << (*it)->get_money() << "\t     "
		<< (*it)->get_magicPower() << "\t  " << (*it)->get_strength() << "\t\t   " << (*it)->get_dexterity() << "\t\t  " << (*it)->get_agility() << "\t\n";
	cout << BYELL << "=======================================================================================================================" << RESTORE << endl;
}

list<Hero*> HeroesTeam::get_myHeroes() { return myHeroes; }

Location* HeroesTeam::get_location() { return location; }

// the hero from the Team, the player chose, is returned
Hero* HeroesTeam::pickHeroFromTeam() {
	cout << "Please give the name of the hero:";
	string h_name;
	cin >> h_name;
	Hero* pickedHero;
	while((pickedHero = validHeroName(h_name)) == NULL) {
		cout << "No hero in your Team exists, with that name! Please try again: ";
		cin >> h_name;
	}
	return pickedHero;
}

// returns NULL if no Hero exists in the Team with that h_name, 
// the Hero with that h_name is returned otherwise
Hero* HeroesTeam::validHeroName(string h_name) {
	list<Hero*>::iterator it;
	for (it = myHeroes.begin(); it != myHeroes.end(); ++it)
		if ((*it)->get_name() == h_name)
			return *it;
	return NULL;
}

void HeroesTeam::printHeroes() {
	cout << BYELL << "=========================================================== My Team ============================================================" << RESTORE << endl;
	cout << "Name\t\t" << BGREEN << "Level\t" << "Money\t " << "MagicPower\t" << RESTORE << "HealthPower\t" << "Experience\t" << "Strength\t" << "Dexterity\t" << "Agility" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
	for (list<Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it)
		cout << UWHITE << (*it)->get_name() << RESTORE << "\t  " << BGREEN << (*it)->get_level() << "\t "
		<< (*it)->get_money() << "\t   " << (*it)->get_magicPower() << RESTORE << BWHITE <<  "\t\t   " << (*it)->get_healthPower() << "\t\t    "
		<< (*it)->get_experience() << "\t\t  " << (*it)->get_strength() << "\t\t  "<< (*it)->get_dexterity() << "\t\t  " << (*it)->get_agility() << RESTORE << "\t\n";
	cout << BYELL << "=================================================================================================================================" << RESTORE << endl;
}