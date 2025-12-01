#ifndef _Human_H
#define _Human_H

#include "Organism.h"
#include "GameSpecs.h"

class Human : public Organism
{
protected:
	int recruitCounter = HUMAN_BREED;

public:
	Human(); 
	Human( City *city, int size);
	virtual ~Human();

	void turn(); //all things a human may do on their turn. i.e. a move, and if allowed a recruitment
	virtual char getChar() const override { return HUMAN_CH; }
};

#endif
