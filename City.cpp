//
// Created by zdrol on 2025-11-25.
//

#include "lib/City.h"
#include "lib/Organism.h"

//Default Constructor
City::City() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
};

//Virtual destructor
City::~City() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            delete grid[i][j];
        }
    }
};

//Get location in the city for an organism
Organism *City::getOrganism( int x, int y ) {
    if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE) return nullptr;
    return grid[x][y];
};
//Set location in the city of an organism
void City::setOrganism( Organism *organism, int x, int y ) {
    if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE) return;
    grid[x][y] = organism;
};

//What happens on a step/turn
void step() {

}; //includes all actions except reset, counting, and printing in this solution.

//Resets the city
void City::reset() {
    for (int i = 0; i < GRIDSIZE; ++i)
        for (int j = 0; j < GRIDSIZE; ++j)
            if (grid[i][j]) grid[i][j]->setMoved(false);
};

//Gets type count for char
int City::countType(char type) {
    int ct = 0;
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
            if (grid[i][j] && grid[i][j]->getChar() == type) ct++;

    return ct;
};

//Overrides cout << operator for city object
ostream& operator<<( ostream &output, City &city ) {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (city.grid[i][j]) output << city.grid[i][j]->getChar();
        }
        output << "\n";
    }
    return output;
};

//Color settings
void col(int c) {

};
