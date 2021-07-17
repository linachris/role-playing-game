#include <iostream>
#include <cstring>
#include "Items.h"

/******************************** Item ********************************/
Item::Item(const string nam, const int cst, const int level)
: name(nam), cost(cst), minLevel(level), used(true) {}

Item::~Item() {}

string Item::get_name()  { return name; }

int Item::get_cost() { return cost; }

int Item::get_minLevel() { return minLevel; }

bool Item::get_used() { return used; }

void Item::set_used(bool state) { used = state; }

int Item::get_damage() { return 0; }

int Item::get_handsNeeded() { return 0; }

int Item::get_defence() { return 0; }

int Item::get_IncreaseTrait() { return 0; }

void Item::set_damage(int strength) { strength++; }

string Item::get_type() { return NULL; }

/******************************** Weapon ********************************/
Weapon::Weapon(const string nam, const int cst, const int level, const int dmg, const int hndsNeed)
: Item(nam, cst, level), damage(dmg), handsNeeded(hndsNeed) {}

Weapon::~Weapon()  {}

int Weapon::get_damage() { return damage; }

int Weapon::get_handsNeeded() { return handsNeeded; }

string Weapon::get_item_kind() { return "Weapon"; }

void Weapon::set_damage(int strength) { damage += strength; }

/******************************** Armor ********************************/
Armor::Armor(const string nam, const int cst, const int level, const int dfence)
: Item(nam, cst, level), defence(dfence), handsNeeded(1) {}

Armor::~Armor() {}

int Armor::get_defence() { return defence; }

int Armor::get_handsNeeded() { return handsNeeded; }

string Armor::get_item_kind() { return "Armor"; }

/******************************** Potion ********************************/
Potion::Potion(const string nam, const int cst, const int level, const int incrTrait, const string type)
:Item(nam, cst, level), increaseTrait(incrTrait), type(type) {}

Potion::~Potion() {}

int Potion::get_IncreaseTrait() { return increaseTrait; }

string Potion::get_item_kind() { return "Potion"; }

string Potion::get_type() { return type; }