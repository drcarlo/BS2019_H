#include "battleships.h"
#include <iostream>
#include <time.h>
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));

	unsigned int size, shipNum;
	// no test for sizes here - thrust to user to get it right
	cout << "Input size and ship num: ";
	cin >> size >> shipNum;

	board b(size, shipNum);
	b.display();

	// game loop 
	do {
		unsigned int x, y;
		do {
			b.display();
			cout << "Input Coordinates: ";
			cin >> x >> y;
		} while (!b.tryHit(x, y));
		b.display();
	} while (!b.terminate());

	cout << endl << "Final Score is: " << b.getScore() << endl;;
	return 0;
}