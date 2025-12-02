//
// Created by zdrol on 2025-12-02.
//

#include "lib/Building.h"
#include "lib/GameSpecs.h"
#include <algorithm>
#include <ranges>

#include "lib/City.h"
#include "lib/Human.h"

Building::Building()
    : Organism(nullptr, 1), humans(0)
{}

Building::Building(City *city, int size)
    : Organism(city, size), humans(0)
{}

Building::~Building() {
    //Delete humans still inside too
    for (Human *h : humans) {
        delete h;
    }
    humans.clear();
}

bool Building::enter(Human *h) {
    if (!h) return false;
    if ((int)humans.size() >= BUILDING_MAX) return false;
    humans.push_back(h);
    return true;
}

bool Building::isFull() const {
    return (int)humans.size() >= BUILDING_MAX;
}

int Building::getOccupancy() const {
    return static_cast<int>(humans.size());
}

void Building::turn() {
    if (!city) return;

    const std::vector<std::pair<int,int>> dirs = { //8 directions (from zombie)
        {-1,-1},{-1,0},{-1,1},
        {0,-1},         {0,1},
        {1,-1}, {1,0},  {1,1}
    };

    int bx = getX();
    int by = getY();

    bool safe = true;
    for (auto &d : dirs) { //AI Suggestion (cleaner)
        int nx = bx + d.first;
        int ny = by + d.second;
        if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) return;
        if (city->getOrganism(nx, ny) != nullptr) return;
    }
    if (humans.empty()) return;

    const std::vector<std::pair<int,int>> releaseOrder = {
        {-1,0},{1,0},{0,-1},{0,1},
        {-1,-1},{-1,1},{1,-1},{1,1}
    };

    for (auto &d : releaseOrder) {
        if (humans.empty()) break;
        int nx = bx + d.first;
        int ny = by + d.second;
        if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
        if (city->getOrganism(nx, ny) == nullptr) {
            Human *h = humans.back();
            humans.pop_back();
            city->setOrganism(h, nx, ny);
            h->setPosition(nx, ny);
            h->setMoved(true);
            h->setInside(false);
            h->setHome(nullptr);
        }
    }

}
