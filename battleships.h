#pragma once

class board
{
	enum cell { sea = 0, ship = 1, hit = 2, miss = 3 };
	unsigned int size;
	int** map;
	unsigned int shipNum;
	unsigned int hitShips;
	unsigned int score;
public:
	board(unsigned int _size, unsigned int _shipNum);
	~board();
	void save();
	void load();
	void display();
	bool tryHit(unsigned int x, unsigned int y);
	bool terminate();
	unsigned int getScore();

private:
	// place the ship - return success or not
	bool placeShip(unsigned int x, unsigned int y);
	//initialise ships
	void initialiseShips();
};