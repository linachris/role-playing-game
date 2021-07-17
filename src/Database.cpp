#include "Database.h"
#include <fstream>
#include <iostream>
using namespace std;

Database::Database() {

	string name;
	int level,damageRate,defence,agility;

	/************************* Dragons *************************/
	ifstream Dragon("txt/Dragons.txt");
	if (!Dragon) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while(Dragon >> name >> level >> damageRate >> defence >> agility)
		insertDragon(name, level, damageRate, defence, agility);

	/************************* Exoskeletons *************************/
	ifstream Exoskeleton("txt/Exoskeletons.txt");
	if (!Exoskeleton) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while(Exoskeleton >> name >> level >> damageRate >> defence >> agility)
		insertExoskeleton(name, level, damageRate, defence, agility);

	/************************* Spirits *************************/
	ifstream Spirit("txt/Spirits.txt");
	if (!Spirit) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while(Spirit >> name >> level >> damageRate >> defence >> agility)
		insertSpirit(name, level, damageRate, defence, agility);

	//Heroes......
	int magicPower,dexterity,strength;

	/************************* Warriors *************************/
	ifstream Warrior("txt/Warriors.txt");
	if (!Warrior) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while(Warrior >> name  >> magicPower >> strength >> dexterity >> agility)
		insertWarrior(name, magicPower, strength, dexterity, agility);

	/************************* Sorcerers *************************/
	ifstream Sorcerer("txt/Sorcerers.txt");
	if (!Sorcerer) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while(Sorcerer >> name  >> magicPower >> strength >> dexterity >> agility)
		insertSorcerer(name, magicPower, strength, dexterity, agility);

	/************************* Paladins *************************/
	ifstream Paladin("txt/Paladins.txt");
	if (!Paladin) {
		cout << "While opening a file an error was encountered" << endl;
		return;
	}
	while(Paladin >> name  >> magicPower >> strength >> dexterity >> agility)
		insertPaladin(name, magicPower, strength, dexterity, agility);
	effects("info");		// printing some middle-earth effects
	chooseYourTeam();		// player is prompted to choose a HeroesTeam 
}

Database::~Database() {
	delete team;
	while (!paladins.empty()) {
		delete paladins.back();
		paladins.pop_back();
	}
	while (!sorcerers.empty()) {
		delete sorcerers.back();
		sorcerers.pop_back();
	}
	while (!warriors.empty()) {
		delete warriors.back();
		warriors.pop_back();
	}
	while (!spirits.empty()) {
		delete spirits.back();
		spirits.pop_back();
	}
	while (!exoskeletons.empty()) {
		delete exoskeletons.back();
		exoskeletons.pop_back();
	}
	while (!dragons.empty()) {
		delete dragons.back();
		dragons.pop_back();
	}
}

void Database::insertWarrior(const string name, const int magicPower, const int strength, const int dexterity, const int agility) {
	Warrior* warrior = new Warrior(name, magicPower, strength, dexterity, agility);
	warriors.push_back(warrior);
}

void Database::insertSorcerer(const string name, const int magicPower, const int strength, const int dexterity, const int agility) {
	Sorcerer* sorcerer = new Sorcerer(name, magicPower, strength, dexterity, agility);
	sorcerers.push_back(sorcerer);
}

void Database::insertPaladin(const string name, const int magicPower, const int strength, const int dexterity, const int agility) {
	Paladin* paladin = new Paladin(name, magicPower, strength, dexterity, agility);
	paladins.push_back(paladin);
}

void Database::insertDragon(const string name, const int level, const int damageRate, const int defence, const int agility) {
	Dragon* dragon = new Dragon(name, level, damageRate, defence, agility);
	dragons.push_back(dragon);
}

void Database::insertExoskeleton(const string name, const int level, const int damageRate, const int defence, const int agility) {
	Exoskeleton* exoskeleton = new Exoskeleton(name, level, damageRate, defence, agility);
	exoskeletons.push_back(exoskeleton);
}

void Database::insertSpirit(const string name, const int level, const int damageRate, const int defence, const int agility) {
	Spirit* spirit = new Spirit(name, level, damageRate, defence, agility);
	spirits.push_back(spirit);
}

void Database::chooseYourTeam() {
	cout << "Please choose your team(from 1 to 3 heroes): \n\n";

	cout << "================================ Available Warriors =================================\n";
	cout << "Name\t\t" << "    Magic Power\t\t" << "\b\bStrength\t\t" << "Dexterity\t" << "Agility\t\t" << endl;
	cout << "-------------------------------------------------------------------------------------\n";
	for (list<Warrior*>::iterator it = warriors.begin(); it != warriors.end(); ++it)
		cout << (*it)->get_name() << "\t\t" << (*it)->get_magicPower() << "\t\t" << (*it)->get_strength() << "\t\t  " << (*it)->get_dexterity() << "\t\t  " << (*it)->get_agility() << "\t\n";

	cout << endl;

	cout << "=============================== Available Sorcerers ================================\n";
	cout << "Name\t\t" << "    Magic Power\t\t" << "\b\bStrength\t\t" << "\bDexterity\t" << "Agility\t\t" << endl;
	cout << "-------------------------------------------------------------------------------------\n";
	for (list<Sorcerer*>::iterator it = sorcerers.begin(); it != sorcerers.end(); ++it)
		cout << (*it)->get_name() << "\t\t" << (*it)->get_magicPower() << "\t\t" << (*it)->get_strength() << "\t\t  " << (*it)->get_dexterity() << "\t\t  " << (*it)->get_agility() << "\t\n";

	cout << endl;

	cout << "================================ Available Paladins =================================\n";
	cout << "Name\t\t" << "    Magic Power\t\t" << "\b\bStrength\t\t" << "\bDexterity\t" << "Agility\t\t" << endl;
	cout << "-------------------------------------------------------------------------------------\n";
	for (list<Paladin*>::iterator it = paladins.begin(); it != paladins.end(); ++it)
		cout << (*it)->get_name() << "\t\t" << (*it)->get_magicPower() << "\t\t" << (*it)->get_strength() << "\t\t  " << (*it)->get_dexterity() << "\t\t  " << (*it)->get_agility() << "\t\n";

	cout << endl;

	string hero_name;
	list<Hero*> heroes_choosen;

	// pushing the heroes the player chose to a list, and calling the HeroesTeam constuctor!
	for (int i = 0; i < 3; i++) {
		cout << "Please select a hero: ";
		cin >> hero_name;
		Hero* heroToAdd;
		while ((heroToAdd = validHeroName(hero_name)) == NULL) {
			cout << "No hero with that name exists, please try again: ";
			cin >> hero_name;
		}
		// the hero's name is valid - check if the hero's already been chosen - add hero to the team!
		bool alreadyChoosen = 0;
		for (list<Hero*>::iterator it = heroes_choosen.begin(); it != heroes_choosen.end(); ++it)
			if ((*it)->get_name() == hero_name) {
				cout << "You have already choosen that hero! Please choose another one: ";
				i--;
				alreadyChoosen = 1;
				break;
			}
		if (alreadyChoosen)
			continue;

		heroes_choosen.push_back(heroToAdd);
		int heroes_num = 0;
		cout << "\n>>>>>> Your Team Members: ";
		for (list<Hero*>::iterator it = heroes_choosen.begin(); it != heroes_choosen.end(); ++it)
			cout << ++heroes_num << "." << (*it)->get_name() << " ";
		cout << "<<<<<<\n";

		if (i < 2) {
			cout << "\nDo you want to choose another player; (Type \"yes\" or \"no\"): ";
			string answer;
			cin >> answer;
			while ((answer != "yes") && (answer != "no")) {
				cout << "Expected \"yes\" or \"no\", please try again: ";
				cin >> answer;
			}
			if (answer == "no")
				break;
			// else asks the player to choose another one
		}
	}
	cout << endl;

	// now we have all the heroes of player's choice! construct the HeroesTeam
	team = new HeroesTeam(heroes_choosen);
}

// returns NULL if no hero exists with that h_name - the hero is returned if exists
Hero* Database::validHeroName(string h_name) {
	for (list<Warrior*>::iterator it = warriors.begin(); it != warriors.end(); ++it)
		if ((*it)->get_name() == h_name)
			return *it;

	for (list<Sorcerer*>::iterator it = sorcerers.begin(); it != sorcerers.end(); ++it)
		if ((*it)->get_name() == h_name)
			return *it;

	for (list<Paladin*>::iterator it = paladins.begin(); it != paladins.end(); ++it)
		if ((*it)->get_name() == h_name)
			return *it;
	return NULL;
}

HeroesTeam* Database::get_myHeroesTeam() { return team; }

list <Monster*> Database::monsterGenerator() {
	//there are 3 monster types. (1:Dragon , 2:Exoskeleton, 3:Spirit)
	int type = 1; 						//so we choose one of the 3
	list <Monster*> mchoosen;
	list <Hero*> mHeroes = team->get_myHeroes();
	for(list<Hero*>::iterator iter = mHeroes.begin(); iter != mHeroes.end(); ++iter) {
		if(type == 1) {
			for (list<Dragon*>::iterator it = dragons.begin(); it != dragons.end(); ++it) {
				if((*iter)->get_level() == (*it)->get_level()) {
					Dragon* dr = *it;
					Monster* mToPush = new Dragon(dr->get_name(), dr->get_level(), dr->get_damageRate(), dr->get_defence(), dr->get_agility());
					mchoosen.push_back(mToPush);
					break;
				}
			}
		}
		else if(type == 2) {
			for (list<Exoskeleton*>::iterator it = exoskeletons.begin(); it != exoskeletons.end(); ++it) {
				if((*iter)->get_level() == (*it)->get_level()) {
					Exoskeleton* ex = *it;
					Monster* mToPush = new Exoskeleton(ex->get_name(), ex->get_level(), ex->get_damageRate(), ex->get_defence(), ex->get_agility());
					mchoosen.push_back(mToPush);
					break;
				}
			}
		}
		else if(type == 3) {
			for (list<Spirit*>::iterator it = spirits.begin(); it != spirits.end(); ++it) {
				if((*iter)->get_level() == (*it)->get_level()) {
					Spirit* sp = *it;
					Monster* mToPush = new Spirit(sp->get_name(), sp->get_level(), sp->get_damageRate(), sp->get_defence(), sp->get_agility());
					mchoosen.push_back(mToPush);
					break;
				}
			}
		}
		type++;
	}
	return mchoosen;
}

void Database::effects(string effect) {
	if (effect == "heroes") {
		cout << BBLUE << "      .-.      _\n" << "    __|=|__   /|\n" << "   (_/`-`\\_) //\n" 
		<< "   //\\___/\\ //		              WE WON, WE WON!!\n" << "   <>/   \\<>/	 		THE MONSTERS ARE ALL DEAD!!\n"
		<< "    \\|_._|/		  LET'S GO GRAB A BEER AND GET SOME REST!\n" << "     <_I_>\n" << "      |||\n" << "     /_|_\\\n" << RESTORE;
	}
	else if (effect == "monsters") {
		cout  << BRED << "      _,     ,_\n" << "    .'/  ,_   \'.\n" << "   |  \\__( >__/  |			     OH NO..THE ENEMY WON..\n"
		<< "   \\             /		LET'S GET SOME REST TO HEAL AND REGAIN OUR STRENGTH!\n" << "    '-..__ __..-'\n" << "         /_\\\n";
	}
	else if (effect == "info") {
	cout << BBLUE << "                                                  |>>>\n ";
	cout << "                                                 |\n";
	cout << "   WELCOME TO THE REALM OF MIDDLE EARTH.    _  _|_  _		HOW TO PLAY :\n";
	cout << "     THE REALM OF WARRIORS, SORCERERS,     |;|_|;|_|;|		When asked, just type with your keyboard and press ENTER\n";
	cout << "  AND PALADINS. IN YOUR JOURNEY, YOU WILL  \\\\.    .  /	\n";
	cout << "     COME ACROSS DRAGONS, EXOSKELETONS      \\\\:  .  / 		- move up (w)\n";
	cout << "     AND SPIRITS. DONT LOSE YOUR FAITH,      ||:   |		- move down(s)\n";
	cout << " DONT'T HESITATE, AND FIGHT WITH YOUR SOUL.  ||:.  |		- move left (a)\n";
	cout << "                                             ||:  .|		- move right(d)\n";
	cout << "     YOU CAN WANDER INTO THIS WORLD,         ||:   |       \\,/\n";
	cout << "   AND VISIT THE MARKET TO BUY WEAPONS,      ||: , |            /`\\\n";
	cout << "     ARMOR, POTIONS & SPELLS, TO KEEP        ||:   |		AND REMEMBER: FEAR IS FOR THE WEAK, AND\n";
	cout << "               YOU ALIVE!                    ||: . |		              ALL THAT GLITTERS IS NOT GOLD!\n";
	cout << "              __                            _||_   |\n";
	cout << "     ____--`~    '--~~__            __ ----~    ~`---,              ___\n";
	cout << "-~--~                   ~---__ ,--~'                  ~~----_____-~'   `~----~~~~----_____-~'   `~----~~\n" << RESTORE;
	}
}