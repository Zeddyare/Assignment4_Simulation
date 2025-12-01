//
// Created by zdrol on 2025-11-25.
//

#include "lib/Human.h"
#include "lib/Zombie.h"
#include "lib/City.h"

//Default constructor for a human
Human::Human()
    : Organism(nullptr, 1), recruitCounter(0)
{}

//Constructor for a human within the city
Human::Human( City *city, int size)
    : Organism(city, size), recruitCounter(0)
{}

//Human virtual destructor
Human::~Human() = default;

//What a human does on its turn (can only move X or Y)
void Human::turn() {

    if (hasMoved()) return;

    int ox = getX();
    int oy = getY();

    const int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; //AI Rec to keep orthogonal directions only
    int emptyCt = 0;
    int emptyTargets[4][2];


    //Looks for empty squares
    for (int i = 0; i < 4; ++i) {
        int nx = ox + dirs[i][0];
        int ny = oy + dirs[i][1];
        if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
            Organism *o = city->getOrganism(nx, ny);
            //Finds only totally open squares
            if (o == nullptr) {
                emptyTargets[emptyCt][0] = nx;
                emptyTargets[emptyCt][1] = ny;
                emptyCt++;
            }
        }

    //For moving into empty squares
    if (emptyCt > 0) {
        int idx = rand() % emptyCt;
        int tx = emptyTargets[idx][0];
        int ty = emptyTargets[idx][1];

        city->setOrganism(nullptr, ox, oy);
        city->setOrganism(this, tx, ty);
        setPosition(tx, ty);
        setMoved(true);
    }
    recruitCounter++;

    //AI Refactor for safer checking/breed routine
    if (recruitCounter >= HUMAN_BREED) {
        int bx = getX();
        int by = getY();
        int breedEmptyCt = 0;
        int breedEmpty[4][2];

        for (int i = 0; i < 4; ++i) {
            int nx = bx + dirs[i][0];
            int ny = by + dirs[i][1];
            if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
            Organism *o = city->getOrganism(nx, ny);
            if (o == nullptr && breedEmptyCt < 4) {
                breedEmpty[breedEmptyCt][0] = nx;
                breedEmpty[breedEmptyCt][1] = ny;
                ++breedEmptyCt;
            }
        }

        if (breedEmptyCt > 0) {
            int idx = rand() % breedEmptyCt;
            int tx = breedEmpty[idx][0];
            int ty = breedEmpty[idx][1];

            Human *recruit = new Human(city, 1);
            city->setOrganism(recruit, tx, ty);
            recruit->setPosition(tx, ty);
            recruit->setMoved(true);
        }

        //Success indifferent reset
        recruitCounter = 0;
    }

};

