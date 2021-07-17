#include "Spells.h"
using namespace std;

/*********************************** Spell functions ***********************************/
Spell::Spell(const string name, const int price, const int level, const int damageRange, const int magic_energy)
:name(name),cost(price),minLevel(level),damageRange(damageRange),minMagPower(magic_energy) {}

Spell::~Spell() {}

string Spell::get_name(){ return name; }

int Spell::get_cost(){ return cost; }

int Spell::get_minLevel(){  return minLevel; }

int Spell::get_damageRange(){ return damageRange; }

int Spell::get_minMagPower(){ return minMagPower; }

string Spell::get_spell_type() { return "spell"; }

int Spell::get_decrDamageRate() { return 0; }

int Spell::get_decrDefence() { return 0; }

int Spell::get_decrAgility() { return 0; }

/*********************************** IceSpell functions ***********************************/
IceSpell::IceSpell(const string name, const int price, const int level, const int damage_rate, const int magic_energy, const int decrDamageRate)
:Spell(name,price,level,damage_rate,magic_energy), decrDamageRate(decrDamageRate) {}

IceSpell::~IceSpell() {}

string IceSpell::get_spell_type() { return "IceSpell"; }

int IceSpell::get_decrDamageRate() { return decrDamageRate; }

/*********************************** FireSpell functions ***********************************/
FireSpell::FireSpell(const string name, const int price, const int level, const int damage_rate, const int magic_energy, const int decrDefence)
:Spell(name,price,level,damage_rate,magic_energy), decrDefence(decrDefence) {}

FireSpell::~FireSpell() {}

string FireSpell::get_spell_type() { return "FireSpell"; }

int FireSpell::get_decrDefence() { return decrDefence; }

/*********************************** LightingSpell functions ***********************************/
LightingSpell::LightingSpell(const string name, const int price, const int level, const int damage_rate, const int magic_energy, const int decrAgility)
:Spell(name,price,level,damage_rate,magic_energy), decrAgility(decrAgility) {}

LightingSpell::~LightingSpell() {}

string LightingSpell::get_spell_type() { return "LightingSpell"; }

int LightingSpell::get_decrAgility() { return decrAgility; }