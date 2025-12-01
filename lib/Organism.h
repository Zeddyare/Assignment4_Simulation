// cpp
#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	int size;
	bool moved;
	City *city;

public:
	Organism();
	Organism( City *city, int size);
	virtual ~Organism();

	// Behavior
	virtual void turn() = 0;
	virtual char getChar() const = 0; // allow callers to identify type

	// Controlled accessors for protected state (so other classes can "access" protected members)
	int getX() const;
	int getY() const;
	void setPosition(int nx, int ny);

	bool hasMoved() const;
	void setMoved(bool mv);

	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
