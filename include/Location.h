#pragma once

class Location {
	int row;
	int column;
  public:
	Location();
	~Location();
    bool compare(int x, int y);
    int get_row();
    int get_column();
	void update(int x, int y);
};