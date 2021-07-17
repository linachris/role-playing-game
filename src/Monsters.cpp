#include "Livings.h"
using namespace std;

/*********************************** Monster functions ***********************************/
Monster::Monster(const string name, const int level, const int damageRate, const int defence, const int agility)
: Living(name,level),damageRate(damageRate),defence(defence),agility(agility) {}

Monster::~Monster() {}

/*********************************** Dragon functions ***********************************/
Dragon::Dragon(const string name, const int level, const int damageRate, const int defence, const int agility)
: Monster(name,level,damageRate,defence,agility) {}

Dragon::~Dragon() {}

/******************************** Exoskeleton functions ********************************/
Exoskeleton::Exoskeleton(const string name, const int level, const int damageRate, const int defence, const int agility)
: Monster(name,level,damageRate,defence,agility) {}

Exoskeleton::~Exoskeleton(){}

/********************************** Spirit functions ***********************************/
Spirit::Spirit(const string name, const int level, const int damageRate, const int defence, const int agility)
: Monster(name,level,damageRate,defence,agility) {}

Spirit::~Spirit(){}

int Monster::get_damageRate(){ return damageRate;}

int Monster::get_defence(){ return defence;}

int Monster::get_agility(){ return agility;}

void Monster::set_defence(int decrease) {
	defence -= decrease;
	if(defence < 0) defence = 0 ;
}

void Monster::set_damageRate(int decrease) {
	damageRate -= decrease;
	if(damageRate < 0) damageRate = 0;
}

void Monster::set_agility(int decrease) {
	agility -= decrease;
	if(agility < 0) agility = 0;
}