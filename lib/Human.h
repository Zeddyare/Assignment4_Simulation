#ifndef _Human_H
#define _Human_H


#include "Organism.h"
#include "GameSpecs.h"

class Building;

class Human : public Organism
{
protected:
	int recruitCounter; //= HUMAN_BREED;
	bool inside;
	Building *home;

public:
	Human(); 
	Human( City *city, int size);
	virtual ~Human();

	void turn(); //all things a human may do on their turn. i.e. a move, and if allowed a recruitment
	virtual char getChar() const override { return HUMAN_CH; }

	//For buildings
	bool isInside() const { return inside; }
	void setInside(bool state) { inside = state;}
	void setHome(Building *b) { home = b; }
	Building* getHome() const { return home; }
};

#endif
