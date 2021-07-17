#include "Grid.h"
#include <iostream>
#include <cstdlib>
using namespace std;

#define NON 'N'
#define COMMON ' '
#define MARKET 'M'

Grid::Grid(Market* m, Database* d) {
	gameMarket = m;
	livings = d;

    map = new char*[LENGTH];
	for (int i = 0; i < LENGTH; i++) {
        map[i] = new char[WIDTH];
    }
    for (int i = 0; i < LENGTH; i++){
		for (int j = 0; j < WIDTH; j++)
            map[i][j] = NON;
	}

	map[0][0] = COMMON;     // the players starts at a common block
	map[0][1] = MARKET;     // and can visit the market at the beginning of the game

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int typeOfBlock = rand()%100;
            // in case no block around is accessible
            if ((j > 0) && (i > 0) && (j < WIDTH - 1) && (i < LENGTH - 1) 
				&& (map[i][j-1] == NON) && (map[i-1][j] == NON) && (map[i][j+1] == NON) && (map[i+1][j] == NON))
                map[i][j] = COMMON;
            else if (typeOfBlock <= 15)
                map[i][j] = NON;
            else if ((typeOfBlock > 15) && (typeOfBlock <= 45))
                map[i][j] = MARKET;
            else if ((typeOfBlock > 45) && (typeOfBlock <= 100))
                map[i][j] = COMMON;
        }
    }
    map[0][0] = COMMON;     // the players starts at a common block
    map[0][1] = MARKET;     // and can visit the market at the beginning of the game
}

Grid::~Grid() {
    for (int i = 0; i < LENGTH; i++)
        delete[] map[i];
    delete[] map;
}

// returns false if the player wants to quit the game, else true
bool Grid::move() {

	displayMap();
	cout << "Where do you wanna go next?\n";
	cout << IYELL << "Press \"s\" to move down, \"w\" to move up, \"a\" to move left, \"d\" to move right or \"quit\"\n" << RESTORE;
	cout << "Your team is moving: ";

	string move;
	cin >> move;
	while ((move != "s") && (move != "w") && (move != "a") && (move != "d") && (move != "quit")) {
		cout << "Not a valid move, your team can only move down/up/left/right, please try again!\n";
		cout << IYELL << "Press \"s\" to move down, \"w\" to move up, \"a\" to move left, \"d\" to move right or \"quit\"\n" << RESTORE;
		cout << "Your team is moving: ";
		cin >> move;
	}
	// valid input move by user - see if it's a valid move at the map too
	bool validMove = false;
	while (!validMove) {
		if (move == "s") {
			if (move_down())		// valid move at the map
				validMove = true;
			else 					// invalid move at the map
				cout << REDFUL << "You can't go there, or you'll drift away from this universe!" << RESTORE << endl;
		}
		else if (move == "w") {
			if (move_up())
				validMove = true;
			else
				cout << REDFUL << "You can't go there, or you'll drift away from this universe!" << RESTORE << endl;
		}
		else if (move == "a") {
			if (move_left())
				validMove = true;
			else
				cout << REDFUL << "You can't go there, or you'll drift away from this universe!" << RESTORE << endl;
		}
		else if (move == "d") {
			if (move_right())
				validMove = true;
			else
				cout << REDFUL << "You can't go there, or you'll drift away from this universe!" << RESTORE << endl;
		}
		else if (move == "quit") {
			cout << URED << "Are you sure you want to quit? All your progress will be lost!" << RESTORE << "(Type \"yes\" or \"no\"): ";
			string answer;
			cin >> answer;
			while ((answer != "yes") && (answer != "no")) {
				cout << "Expected \"yes\" or \"no\", please try again: ";
				cin >> answer;
			}
			if (answer == "yes")		// quiting the game
				return false;
			// else continue playing
		}
		displayMap();
		if (!validMove) {
			cout << REDFUL << "Try moving to a different area:" << RESTORE;
			cin >> move;
		}
	}
	// now we have a valid move
	examineArea();
	return true;
}

bool Grid::move_up() {
    int x = get_TeamLocation()->get_row();
    int y = get_TeamLocation()->get_column();
    if (x > 0) {
        if (map[x-1][y] == NON)					// NON ACCESSIBLE AREA - can't move there
            return false;
        get_TeamLocation()->update(x-1, y);		// ACCESSIBLE AREA - update team's position in map
        return true;
    }
    return false;
}

bool Grid::move_down() {
    int x = get_TeamLocation()->get_row();
    int y = get_TeamLocation()->get_column();
    if (x < LENGTH - 1) {
        if (map[x+1][y] == NON)					// NON ACCESSIBLE AREA - can't move there
            return false;
        get_TeamLocation()->update(x+1, y);		// ACCESSIBLE AREA - update team's position in map
        return true;
    }
    return false;
}

bool Grid::move_right() {
    int x = get_TeamLocation()->get_row();
    int y = get_TeamLocation()->get_column();
    if (y < WIDTH - 1) {
        if (map[x][y+1] == NON)					// NON ACCESSIBLE AREA - can't move there
            return false;
        get_TeamLocation()->update(x, y+1);		// ACCESSIBLE AREA - update team's position in map
        return true;
    }
    return false;
}

bool Grid::move_left() {
    int x = get_TeamLocation()->get_row();
    int y = get_TeamLocation()->get_column();
    if (y > 0) {
        if (map[x][y-1] == NON)					// NON ACCESSIBLE AREA - can't move there
            return false;
        get_TeamLocation()->update(x, y-1);		// ACCESSIBLE AREA - update team's position in map
        return true;
    }
    return false;
}

HeroesTeam* Grid::get_MyTeam() { return livings->get_myHeroesTeam(); }

Location* Grid::get_TeamLocation() { return get_MyTeam()->get_location(); }


void Grid::displayMap() {
    for (int i = 0; i < LENGTH; i++) {
        cout << "-------------------------------------------------------------------------------\n";
        for (int j = 0; j < WIDTH; j++) {
            if (get_TeamLocation()->compare(i,j) == true)
                cout << "||    " << RED << "X" << RESTORE << "    ";
            else if (map[i][j] == NON)
                cout << "||" << BLK << "    " << map[i][j] << "    " << RESTORE;
            else if (map[i][j] == MARKET)
                cout << "||" << PRPL << "    " << map[i][j] << "    " << RESTORE;
            else
                cout << "||    " << map[i][j] << "    ";
        }
        cout << "||\n";
    }
    cout << "-------------------------------------------------------------------------------\n";
    cout << RED << "X" << RESTORE << ": Your Team's position, " << PRPL << "M" << RESTORE << ": Market, " << BLK << "N" << RESTORE << ": NonAccessible Area, The Rest: Common Blocks\n\n";
}

void Grid::examineArea() {
    int x = get_TeamLocation()->get_row();
    int y = get_TeamLocation()->get_column();

	// non-accessible block!
	if (map[x][y] == NON)
		cout << REDFUL << "You can't go there, or you'll drift away from this universe!" << RESTORE << endl;
	else if (map[x][y] == MARKET) {
		cout << PRPL << "Seems like there's a Market nearby! Do you want to visit? " << RESTORE << "(Type \"yes\" or \"no\"): ";
		string answer;
		cin >> answer;
		while ((answer != "yes") && (answer != "no")) {
			cout << "Expected \"yes\" or \"no\", please try again: ";
			cin >> answer;
		}
		if (answer == "yes") 		// visiting the market
			gameMarket->visit(get_MyTeam());
	}
	else if (map[x][y] == COMMON) {
		int possibility = rand() % 101;		// [0,100]
		if (possibility <= 50) {			// No monsters nearby -> no fight
			checkPointRound();
		}
		else {								// a fight will occur with the monsters!
			cout << BRED << "WE ARE UNDER ATTACK! LET'S FIGHT BACK THE MONSTERS!!" << RESTORE << endl;
			fight();
		}
	}
}

void Grid::checkPointMenu() {
	cout << BBLUE << ">>>" << RESTORE << " Press " << BWHITE << "i" << RESTORE << " to " << BWHITE << "Check Inventory" << RESTORE << endl;
	cout << BBLUE << ">>>" << RESTORE << " Press " << BWHITE << "e" << RESTORE << " to " << BWHITE << "Equip Weapons/Armor" << RESTORE << endl;
	cout << BBLUE << ">>>" << RESTORE << " Press " << BWHITE << "u" << RESTORE << " to " << BWHITE << "Use a Potion" << RESTORE << endl;
	cout << BBLUE << ">>>" << RESTORE << " Press " << BWHITE << "c" << RESTORE << " to " << BWHITE << "Continue your journey" << RESTORE << endl;
}

void Grid::checkPointRound() {
	cout << BBLUE <<  "================================== * CHECKPOINT * ====================================" << RESTORE << endl;
	cout << BBLUE << "There are no monsters nearby!" << RESTORE << endl;
	cout << IBLUE << "You can sit by the fire for now, but don't make too much noise, or they will hear you!" << RESTORE << endl;
	cout << IYELL << "In the meantime you can check and upgrade your Team's stats!" << RESTORE << endl;

	bool done = false;
	while (!done) {
		cout << endl;
		checkPointMenu();
		cout << "I want to: ";
		string answ;
		cin >> answ;
		while ((answ != "i") && (answ != "e") && (answ != "u") && (answ != "c")) {
			cout << "Expected one of the options below, please try again!\n";
			checkPointMenu();
			cout << "I want to: ";
			cin >> answ;
		}
		// valid num
		displayTeamStats();
		cout << "Please pick a hero from your team";
		if (answ == "i") {
			cout << " to check inventory: ";
			get_MyTeam()->pickHeroFromTeam()->checkInventoryMenu();
		}
		else if (answ == "e") {
			cout << " to equip weapons/armor: ";
			get_MyTeam()->pickHeroFromTeam()->equip();
		}
		else if (answ == "u") {
			cout << " to use a potion: ";
			get_MyTeam()->pickHeroFromTeam()->use();
		}
		else if ((answ == "c"))		// end of checkpoint round
			break;

		cout << IWHITE << "Do you wish to upgrade the stats of another one of your heroes?" << RESTORE << IYELL << "(Type \"yes\" or \"no\"):" << RESTORE;
		string answer;
		cin >> answer;
		while ((answer != "yes") && (answer != "no")) {
			cout << "Expected \"yes\" or \"no\", please try again: ";
			cin >> answer;
		}
		if (answer == "no")
			done = true;
		// else player is prompted to pick another hero
	}
	cout << "\n" << IBBLUE << "Gather your weapons/armors and wake up the others. The sun has risen, it's time to go!" << RESTORE << endl;
	cout << BBLUE <<  "======================================================================================" << RESTORE << endl;
}

void Grid::displayTeamStats() {
	get_MyTeam()->displayStats();
}

void Grid::fight() {

	list <Monster*> monsters_choosen = livings->monsterGenerator(); 	// choosing the monsters for the battle
	list <Hero*> myHeroes  = get_MyTeam()->get_myHeroes(); 				// fetching my heroes team
	
	int ifHeroFainted = 0;
	int ifMonstFainted = 0;
	short round = 0;

	cout << endl << REDFUL <<  "                                                                                                                       " << RESTORE << endl;
	cout << "\n" << BRED << " >>>>>>>>>> THE TIME FOR OUR REVENGE HAS COME! FIGHT WITH YOUR SOUL! LET'S KILL THESE MONSTERS! <<<<<<<<<<" << RESTORE << endl << endl;
	// when a hero has fainted, the enemy fighting the hero won't fight anymore, so its health is subtracted from the monster's team total healthPower
	while((HeroesHealth(get_MyTeam()->get_myHeroes(), ifMonstFainted) > 0) && (MonstersHealth(monsters_choosen, ifHeroFainted) > 0)) {
		cout << BYELL << "Would you like to display your Team's and Monsters' statistics? (Type \"yes\" or \"no\"): ";
		string answr;
		cin >> answr;
		while ((answr != "yes") && (answr != "no")) {
			cout << "Expected \"yes\" or \"no\", please try again: ";
			cin >> answr;
		}
		cout << endl << REDFUL <<  "======================================================== ROUND " << ++round << " ======================================================" << RESTORE << endl << endl;
		if(answr == "yes") {
			displayTeamStats();
			displayMonStats(monsters_choosen); //and displaying their statistics
		}

		list <Monster*>::iterator m_it = monsters_choosen.begin(); //for each hero there is a monster
		for(list <Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it) {
			if ((*it)->has_fainted()) {
				ifHeroFainted += (*m_it)->get_healthPower();	// to subtract from the monsters team, as the monster is not gonna fight
				++m_it;
				continue;					
			}
 			else if ((*m_it)->has_fainted()) {					//if a monster or hero has fainted -> can't fight!
				ifMonstFainted += (*it)->get_healthPower();		// to subtract from the heroes team, as the hero is not gonna fight
				++m_it;
				continue;
			}
			//for each hero, the player decides whether to attack cast a spell or use a potion
			cout << "\n\nFor this round, choose what you would like for your Hero " << (*it)->get_name() << endl;

			cout << BGREEN << "Do you want to attack, cast a spell or use a potion? (Type: \"attack\",\"cast\" or \"use\"):" << RESTORE;
			string answer;
			cin >> answer;
			while ((answer != "attack") && (answer != "cast") && (answer != "use")) {
				cout << BWHITE << "Expected \"attack\" or \"cast\" or \"use\", please try again: " << RESTORE;
				cin >> answer;
			}

			if(answer == "attack") 
				attack((*it),(*m_it));
			else if(answer == "cast") 
				castSpell((*it),(*m_it));
			else if(answer == "use")
				(*it)->use();
			++m_it;
		}

		list <Hero*>::iterator it = myHeroes.begin(); //for each monster there is a hero
		for(list <Monster*>::iterator m_it = monsters_choosen.begin(); m_it != monsters_choosen.end(); ++m_it) {
			if ((*m_it)->has_fainted()) {
				ifMonstFainted += (*it)->get_healthPower();		// to subtract from the heroes team, as the hero is not gonna fight
				++it;
				continue;					
			}
 			else if ((*it)->has_fainted()) {					//if a monster or hero has fainted -> can't fight!
				ifHeroFainted += (*m_it)->get_healthPower();	// to subtract from the monsters team, as the monster is not gonna fight
				++it;
				continue;
			}
			cout << BGREEN << "\nFor this round, Monster " << (*m_it)->get_name() << " makes an attack!" << RESTORE << endl;
			monster_attack((*it),(*m_it));
			(*it)->free_hands(); //after the monster attack, the hero;s hands must be freed for the new round
			++it;
		}
		// reviving part of the livings' and monsters' health power
		for(list <Monster*>::iterator m_it = monsters_choosen.begin(); m_it != monsters_choosen.end(); ++m_it) {
			if((*m_it)->get_healthPower() != 0) 
				(*m_it)->incr_healthPower(30);
			if ((*m_it)->get_healthPower() > 400)			// restoring health to default
				(*m_it)->set_healthPower(400);
		}

		for(list <Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it) {
			if((*it)->get_healthPower() != 0) 
				(*it)->incr_healthPower(30);			
			if ((*it)->get_healthPower() > 400)			// restoring health to default
				(*it)->set_healthPower(400);
			(*it)->incr_magicPower(30);
		}
		cout << endl << REDFUL <<  "=======================================================================================================================" << RESTORE << endl << endl;
	}

	// if the heroes won
	if(HeroesHealth(get_MyTeam()->get_myHeroes(), 0) > 0) {
		livings->effects("heroes");	// displaying heroes winning 
		float level_factor, monster_factor; //the increase of money depends on the level of the team
		//and of the number of monsters
		for(list <Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it) {
			level_factor = (*it)->get_level()*10;  // prosoxh!! den ginotan pote level

			if(myHeroes.size() == 1) monster_factor = 0.1;
			if(myHeroes.size() == 2) monster_factor = 0.2;
			if(myHeroes.size() == 3) monster_factor = 0.3;

			(*it)->incr_experience(25*monster_factor*level_factor);
			(*it)->incr_money(45*monster_factor*level_factor);

			if((*it)->get_experience() > MAX_EXP((*it)->get_level())) {
				(*it)->levelUp();
				cout << BGREEN << "WOOHOO! Your team just leveled up!!!" << RESTORE << endl;
			}
			if((*it)->has_fainted()) 					//reviving part of the livings' health power if a Hero fainted during the battle
				(*it)->set_healthPower(200);			// and they regain half their initial (healthPower 400/2 = 200)
			if ((*it)->get_healthPower() > 400)			// restoring health to default
				(*it)->set_healthPower(400);
		}
	}
    // if the monsters won - heroes lose(some of them have fainted)
	else if(MonstersHealth(monsters_choosen, 0) > 0) {
		livings->effects("monsters");	// displaying monsters winning 
		for(list <Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it)
		{
			int coins = (*it)->get_money() / 2; 	// if the monsters win the heroes lose half their money
			(*it)->incr_money(-coins);
		
			if((*it)->has_fainted()) 	//reviving part of the livings' health power if a Hero fainted during the battle
				(*it)->set_healthPower(200);			// and they regain half their initial (healthPower 400/2 = 200)
		}
	}
	cout << endl << REDFUL <<  "                                                                                                                       " << RESTORE << endl;
	while (!monsters_choosen.empty()) {
		delete monsters_choosen.back();
		monsters_choosen.pop_back();
	}
}

// if a monster has fainted, the hero is not gonna fight, so we subtract the heroes'(not fighting) health from the team's total health
int Grid::HeroesHealth(list <Hero*> myHeroes, int ifMonstFainted) {
	int sum = 0;
	for(list <Hero*>::iterator it = myHeroes.begin(); it != myHeroes.end(); ++it)
		sum += (*it)->get_healthPower();
	return sum-ifMonstFainted;
}

// if a hero has fainted, the monster is not gonna fight, so we subtract the monsters'(not figthing) health from the Monsters-team's total health
int Grid::MonstersHealth(list <Monster*> monsters_choosen, int ifHeroFainted) {
	int sum = 0;
	for(list <Monster*>::iterator it = monsters_choosen.begin(); it != monsters_choosen.end(); ++it)
		sum += (*it)->get_healthPower();
	return sum-ifHeroFainted;
}


void Grid::displayMonStats(list <Monster*> monsters_choosen) {
	cout << BYELL << "======================================== Monster Stats =========================================\n" << RESTORE;
	cout << "Name\t\t  " << "    Level\t\t" << "\b\b\bHealthPower\t" << "Damage\t\t" << "\bDefence\t\t" << "Agility\t\t" << endl;
	cout << "------------------------------------------------------------------------------------------------\n";
	for(list <Monster*>::iterator it = monsters_choosen.begin(); it != monsters_choosen.end(); ++it)
		cout << UWHITE << (*it)->get_name() << RESTORE << "\t\t" << (*it)->get_level() << "\t\t" << BWHITE << (*it)->get_healthPower() << RESTORE << "\t\t  "
		<< (*it)->get_damageRate() << "\t\t  " << (*it)->get_defence() << "\t\t  " << (*it)->get_agility() << RESTORE << "\t\n";
	cout << BYELL << "================================================================================================\n" << RESTORE;
}

void Grid::attack(Hero* hero, Monster* monster) {
	cout << BGREEN << "Would you like to change your Weapons or Armor? (Type: \"change\" or \"no\"):" << RESTORE;
	string answ;
	cin >> answ;
	while ((answ != "change") && (answ != "no")) {
		cout << BWHITE << "Expected \"change\" or \"no\", please try again: " << RESTORE;
		cin >> answ;
	}
	int strengthRate = hero->get_strength();
	if(answ == "change") {
		Item* equipped;
		if (((equipped = hero->equip()) != NULL) && (equipped->get_item_kind() == "Weapon"))
			strengthRate = equipped->get_damage();	// hero's strength is added to the damage a weapon can cause 
	}
	//if statement is true, the hero holds Armor
	//so monster's damage rate gets decreased
	if(hero->holds_Armor()) 
		monster->set_damageRate(10);

	float agilityRate = monster->get_agility() * 0.1;
	float healthReduction = 0.0;
	healthReduction = abs(monster->get_defence() * static_cast<int>(agilityRate) - strengthRate/5);
	
	monster->decr_healthPower(static_cast<int>(healthReduction*3));
}

void Grid::castSpell(Hero* hero, Monster* monster) {
	if(hero->checkInventory("spells")) {
		while(1) {
			cout << "Give the name of the spell you would like to use(or type \"quit\"):";
			string ToCast;
			cin >> ToCast;
			Spell* spToCast;
			while (((spToCast = hero->validSpellName(ToCast)) == NULL) && (ToCast != "quit")) {
				cout << RED << "No Spell with that name exists in your inventory, please try again(or type \"quit\"): " << RESTORE;
				cin >> ToCast;
			}
			if (ToCast == "quit") 
				break;
			//the damage range of a spell depends on the dexterity range of the hero and
			//is always in that range
			int spell_damage = spToCast->get_damageRange() / hero->get_dexterity();
			monster->set_defence(spell_damage); //the damage the spell causes

			int effectiveness = hero->get_dexterity();
			//we decrease the damageRate, defence and agility
			if(spToCast->get_spell_type() == "IceSpell") monster->set_damageRate(spToCast->get_decrDamageRate());
			else if(spToCast->get_spell_type() == "FireSpell") monster->set_defence(spToCast->get_decrDefence());
			else if(spToCast->get_spell_type() == "LightingSpell") monster->set_agility(spToCast->get_decrAgility());

			cout << BACKROUNDCYAN << "Your hero just casted the Spell " << spToCast->get_name() << " !!" << RESTORE << endl;
			hero->decr_magicPower(spToCast->get_minMagPower());

			float agilityRate = monster->get_agility();
			int healthReduction = 0;
			healthReduction = abs(monster->get_defence() * static_cast<int>(agilityRate) - static_cast<int>(0.1*effectiveness)); //monster's agility supposed to make the health Reduction lesser
			
			monster->decr_healthPower(static_cast<int>(healthReduction/1.5));
			break;
		}
	}
}

void Grid::monster_attack(Hero* hero, Monster* monster) {
	float agilityRate = hero->get_agility() * 0.1;
	float healthReduction = 0.0;
	healthReduction = monster->get_damageRate() * static_cast<int>(agilityRate); //hero's agility supposed to make the health Reduction lesser
	if (static_cast<int>(healthReduction/1.8) < 90)
		hero->decr_healthPower(static_cast<int>(2.6*healthReduction/1.8));
	else if (static_cast<int>(healthReduction/1.8) >= 200)
		hero->decr_healthPower(191);		// if the decrease is reeeally big
	else
		hero->decr_healthPower(static_cast<int>(healthReduction/1.8));
}

void Grid::play() {
	while(move());
}