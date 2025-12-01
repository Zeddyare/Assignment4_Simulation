#ifndef _Zombie_H
#define _Zombie_H

#include "GameSpecs.h"
#include "Organism.h"

class Zombie : public Organism
{
protected:
	int breedCounter = ZOMBIE_BREED;
	int starveCounter = ZOMBIE_STARVE;
public:
	Zombie();
	Zombie( City *city, int size );
	virtual ~Zombie();

	void turn(); //all things a zombie may do on their turn. i.e. an eat/move or a regular move, and if allowed a bite or convert back to human 
	virtual char getChar() const override { return ZOMBIE_CH; }
};

#endif
