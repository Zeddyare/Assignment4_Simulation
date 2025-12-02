//
// Created by zdrol on 2025-11-25.
//

#include "lib/Human.h"
#include "lib/Zombie.h"
#include "lib/City.h"
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

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

    //AI help implementing Vectors instead of strict array
    const std::vector<std::pair<int, int>> dirs =  {{-1,0},{1,0},{0,-1},{0,1}}; //AI Rec to keep orthogonal directions only
    std::vector<int> order = {0, 1, 2, 3};

    static std::default_random_engine rng(
        (unsigned)std::chrono::system_clock::now().time_since_epoch().count()
        );
    std::shuffle(order.begin(), order.end(), rng);


    //Looks for empty squares
    for (int idx : order) {
        int nx = ox + dirs[idx].first;
        int ny = oy + dirs[idx].second;
        if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
        if (city->getOrganism(nx, ny) == nullptr) { //Empty square only
            city->setOrganism(nullptr, ox, oy);
            city->setOrganism(this, nx, ny);
            setPosition(nx, ny); //Move into random empty square in range
            setMoved(true);
            break;
        }
    }
    recruitCounter++;

    //AI Refactor for safer checking/breed routine
    if (recruitCounter >= HUMAN_BREED) {
        std::shuffle(order.begin(), order.end(), rng);
        for (int i : order) {
            int nx = ox + dirs[i].first;
            int ny = oy + dirs[i].second;
            if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
            if (city->getOrganism(ox, oy) == nullptr) {
                auto *recruit = new Human(city, 1);
                city->setOrganism(recruit, ox, oy);
                recruit->setPosition(ox, oy);
                recruit->setMoved(true);
                break;
            }
        }
        //Success indifferent reset
        recruitCounter = 0;
    }
};