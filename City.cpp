//
// Created by zdrol on 2025-11-25.
//

#include "lib/City.h"
#include "lib/Organism.h"
#include "lib/Human.h"
#include "lib/Zombie.h"
#include <windows.h>

//Default Constructor
City::City() {

    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
    generation = 0;

    int humanGen = HUMAN_STARTCOUNT;
    while (humanGen > 0) {
        int hx = rand() % GRIDSIZE;
        int hy = rand() % GRIDSIZE;
        if (grid[hx][hy] == nullptr) {
            auto *human = new Human(this, 1);
            setOrganism(human, hx, hy);
            human->setPosition(hx, hy);
            humanGen--;
        }
    }
    int zombieGen = ZOMBIE_STARTCOUNT;
    while (zombieGen > 0) {
        int zx = rand() % GRIDSIZE;
        int zy = rand() % GRIDSIZE;
        if (grid[zx][zy] == nullptr) {
            auto *zombie = new Zombie(this, 1);
            setOrganism(zombie, zx, zy);
            zombie->setPosition(zx, zy);
            zombieGen--;
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
void City::step() {
    for (int i = 0; i < GRIDSIZE; ++i)
        for (int j = 0; j < GRIDSIZE; ++j)
            if (grid[i][j]) grid[i][j]->turn();
    generation++;
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
            if (city.grid[i][j]) {
                char c = city.grid[i][j]->getChar();
                if (c == HUMAN_CH) city.col(HUMAN_COLOR);
                else if (c == ZOMBIE_CH) city.col(ZOMBIE_COLOR);
                else city.col(DASH_COLOR);
                output << c;
            } else {
                city.col(DASH_COLOR);
                output << SPACE_CH;
            }
        }
        city.col(7); // reset to default color at end of line
        output << "\n";
    }
    city.col(7); // ensure default color on return
    return output;
};

//Color settings
void City::col(int c) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
};

bool City::hasDiversity() {
    int hCt = countType(HUMAN_CH);
    int zCt = countType(ZOMBIE_CH);
    bool isDiverse;

    if (hCt > 0 && zCt > 0) {
        isDiverse = true;
    }
    else {
        isDiverse = false;
    }
    return isDiverse;
}

int City::getGeneration() {
    return generation;
}
