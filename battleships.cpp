#include <iostream>
#include <fstream>
#include <time.h>
#include "battleships.h"

using namespace std;

// two different display possibilities
char dispArray[] = { '~', 'S', 'O', 'X' };
char dispArray2[] = { '~', '~', 'O', 'X' };

board::board(unsigned int _size, unsigned int _shipNum)
{
	// assign the vars
	size = _size; 
	hitShips = 0;
	score = 0; 
	// test for out of bounds
	if (_shipNum > size* size)
		_shipNum = size; 
	shipNum = _shipNum; 
	// allocate memory for grid
	board::map = new int* [size];
	for (unsigned int i = 0; i < size; i++)
		board::map[i] = new int[size];

	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			board::map[i][j] = sea; 
	// place ships
	initialiseShips(); 
}

board::~board() {
	// destroy everything
	for (unsigned int i = 0; i < size; i++)
		delete[] board::map[i];
	delete[] board::map; 
}

void board::save() {
	ofstream fout("map.txt");
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < size; j++) {
			fout << board::map[i][j];
		}
		fout << endl;
	}
	fout.close();
}

void board::load() {
	ifstream fin("map.txt");
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < size; j++) {
			//fin >> map[i][j]; // if you do this you need spaces between elements
			board::map[i][j] = fin.get() - 48;
		}
		fin.ignore();
	}
	fin.close();
	// update numShips after load.
}

void board::display() {
	// clear the screen
	system("cls");
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < size; j++)
			cout << dispArray[board::map[i][j]];
			//cout << dispArray2[map[i][j]];
		cout << endl;
	}
}

bool board::tryHit(unsigned int x, unsigned int y)
{
	if (x == 99 && y == 99) { // Nine nine
		board::save();
		return false;
	}
	if (x == 98 && y == 98) { // Nine-eight? Bad precinct. 
		board::load();
		return false;
	}

	// check for bounds
	if ((x < 0 || x >= size) || (y < 0 || y >= size))
		return false;

	score++; 
	// check if hit test
	if (board::map[x][y] == ship)
	{
		board::map[x][y] = hit;
		hitShips++; 
	}
	else if (board::map[x][y] == sea)
		board::map[x][y] = miss; 

	return true; 
}

bool board::terminate()
{
	return hitShips == shipNum; 
}

unsigned int board::getScore()
{
	return score; 
}

// place the ship - return success or not
bool board::placeShip(unsigned int x, unsigned int y)
{
	if (board::map[x][y] != ship) {
		board::map[x][y] = ship;
		return true;
	}
	else return false;
}

//initialise ships
void board::initialiseShips()
{
	// places all ships
	for (unsigned int i = 0; i < shipNum; i++) {
		unsigned int x, y;
		// test whether ship is placed in the right place
		do {
			x = rand() % size;
			y = rand() % size;
		} while (!placeShip(x, y));
	}
}


