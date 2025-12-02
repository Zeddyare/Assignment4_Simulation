//
// Created by zdrol on 2025-12-02.
//

#ifndef SIMULATION_BUILDING_H
#define SIMULATION_BUILDING_H

#include "Organism.h"
#include "GameSpecs.h"

class Building : public Organism
{
protected:
    int humans;

public:
    Building();
    Building( City *city, int size );
    virtual ~Building();

    void turn();
    void setHumans(int count);
    int getHumans();

    virtual char getChar() const override { return BUILDING_CH; }
};

#endif //SIMULATION_BUILDING_H