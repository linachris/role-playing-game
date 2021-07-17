#include "Location.h"
#include <iostream>
using namespace std;

// The HeroesTeam starts at the first block{0.0} of the grid
Location::Location() : row(0), column(0) {}

Location::~Location() {}

// used to compare a grid's block with the HeroesTeam's location 
bool Location::compare(int x, int y) { return (row == x) && (column == y); }

// used to update the HeroesTeam Location, when having moved on a different block
void Location::update(int x, int y) {
	row = x;
	column = y;
}

int Location::get_row() { return row; }

int Location::get_column() { return column; }