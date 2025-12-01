//
// Created by zdrol on 2025-11-25.
//

#include "lib/Zombie.h"
#include "lib/City.h"
#include "lib/Human.h"

//Default constructor for zombie
Zombie::Zombie()
    : Organism(nullptr, 1), breedCounter(0), starveCounter(0)
{};

//Zombie constructor within city
Zombie::Zombie( City *city, int size )
    : Organism(city, size), breedCounter(0), starveCounter(0)
{}

//Virtual zombie destructor
Zombie::~Zombie() = default;

//Zombie unique turn method (can move diagonally)
void Zombie::turn() {
    if (hasMoved()) return;

    int oldX = getX();
    int oldY = getY();

    //AI assisted in logic (I am not familiar with game/sim design logic)
    int humanCt = 0;
    int humanPos[8][2]; //human position "grid" in relation to zombie, looks 8 directions up to 2 squares away
    int emptyCt = 0;
    int emptyTargets[8][2];


    //Looks for humans in 8 directions
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = oldX + dx, ny = oldY + dy;
            if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
            Organism *o = city->getOrganism(nx, ny);
            if (o && o->getChar() == HUMAN_CH) {
                humanPos[humanCt][0] = nx;
                humanPos[humanCt][1] = ny;
                humanCt++; //If zombie finds any humans within range in 8 directions, adds to count
            } else {
                if (emptyCt < 8) {
                    emptyTargets[emptyCt][0] = nx;
                    emptyTargets[emptyCt][1] = ny;
                    emptyCt++;
                }
            }
        }
    }

    //For eating humans
    if (humanCt > 0 && breedCounter < ZOMBIE_BREED) {
        int idx = rand() % humanCt; //chooses random human within range to target
        int tx = humanPos[idx][0];
        int ty = humanPos[idx][1]; //Searches if human on same Y level or not
        //Human eaten (dead)
        delete city->getOrganism(tx, ty);
        city->setOrganism(nullptr, tx, ty); //Clears space
        //Move into cell
        city->setOrganism(this, tx, ty);
        setPosition(tx, ty);
        setMoved(true);
        starveCounter = 0;
        breedCounter++;

        //For moving into empty squares
         //If 8 steps reached zombie can convert a human in range
    } else if (humanCt > 0 && breedCounter >= ZOMBIE_BREED) {
        int idx = rand() % humanCt;
        int bx = humanPos[idx][0];
        int by = humanPos[idx][0];
        //Human eaten (infected)
        delete city->getOrganism(bx, by);
        Zombie* spawn = new Zombie(city, 1);
        city->setOrganism(spawn, bx, by);
        spawn->setPosition(bx, by);
        spawn->setMoved(true);
        starveCounter = 0;
        breedCounter = 0;

    } else if (emptyCt > 0) {
        int idx = rand() % emptyCt;
        int tx = emptyTargets[idx][0];
        int ty = emptyTargets[idx][1];

        //Move into empty square
        city->setOrganism(nullptr, oldX, oldY);
        city->setOrganism(this, tx, ty);
        setPosition(tx, ty);
        setMoved(true);
        starveCounter++;
        breedCounter++;

        //For no free spaces to move
    } else {
        starveCounter++;
        breedCounter++;
    }


    //Starved conversion
    if (starveCounter >= ZOMBIE_STARVE) {
        int x = getX();
        int y = getY();
        Human *h = new Human(city, 1);
        city->setOrganism(h, x, y);
        h->setPosition(x, y);
        h->setMoved(true);
        delete this;

        return;
    }
};