//
// Created by zdrol on 2025-12-02.
//

#include "lib/Building.h"

Building::Building()
    : Organism(nullptr, 1), humans(0)
{}

Building::Building(City *city, int size)
    : Organism(city, size), humans(0)
{}

Building::~Building() = default;

void Building::turn() {
    //Needed for abstract
}

void Building::setHumans(int count) {
    humans += count;
}
int Building::getHumans() {
    return humans;
}