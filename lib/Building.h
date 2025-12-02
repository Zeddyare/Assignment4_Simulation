//
// Created by zdrol on 2025-12-02.
//

#ifndef SIMULATION_BUILDING_H
#define SIMULATION_BUILDING_H

#include <vector>

#include "Organism.h"
#include "GameSpecs.h"

class Human;

class Building : public Organism
{
protected:
    std::vector<Human*> humans; //Changed to vector for storage of humans (AI Rec)

public:
    Building();
    Building( City *city, int size );
    virtual ~Building();

    void turn();

    bool enter(Human *h);
    bool isFull() const;
    int getOccupancy() const;

    virtual char getChar() const override { return BUILDING_CH; }
};

#endif //SIMULATION_BUILDING_H