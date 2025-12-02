//
// Created by zdrol on 2025-11-25.
//

#include "lib/Zombie.h"
#include "lib/City.h"
#include "lib/Human.h"
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

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

    int ox = getX();
    int oy = getY();

    const std::vector<std::pair<int,int>> dirs = { //8 directions
        {-1,-1},{-1,0},{-1,1},
        {0,-1},         {0,1},
        {1,-1}, {1,0},  {1,1}
    };

    std::vector<int> order(8);
    std::iota(order.begin(), order.end(), 0);


    static std::default_random_engine rng(
        (unsigned)std::chrono::system_clock::now().time_since_epoch().count()
    );

    std::vector<std::pair<int, int>> humans; //Will use emplace_back to append to vectors
    std::vector<std::pair<int, int>> empties;

    //Looks for humans in 8 directions
    //Big help in refactor for vector
    for (int idx : order) {
        int nx = ox + dirs[idx].first;
        int ny = oy + dirs[idx].second;
        if (nx < 0 || nx >= GRIDSIZE || ny < 0 || ny >= GRIDSIZE) continue;
        Organism *o = city->getOrganism(nx, ny);
        if (o && o->getChar() == HUMAN_CH) {
            humans.emplace_back(nx, ny); //Adds humans to the human vector
        } else if (o == nullptr) {
            empties.emplace_back(nx, ny); //Adds free spaces to empties vector
        }
    }

    //AI assist in random selection logic
    auto pick_index = [&](size_t n) -> size_t {
        std::uniform_int_distribution<size_t> dist(0, n - 1);
        return dist(rng);
    };

    //For eating humans
    if (!humans.empty() && breedCounter < ZOMBIE_BREED) {
        size_t pick = pick_index(humans.size());
        int tx = humans[pick].first;
        int ty = humans[pick].second;

        //Human eaten (dead)
        delete city->getOrganism(tx, ty);
        city->setOrganism(nullptr, tx, ty); //Clears space

        //Move into cell
        city->setOrganism(nullptr, ox, oy);
        city->setOrganism(this, tx, ty);
        setPosition(tx, ty);
        setMoved(true);

        starveCounter = 0;
        breedCounter++;


        //If 8 steps reached zombie can convert a human in range
    } else if (!humans.empty() && breedCounter >= ZOMBIE_BREED) {
        size_t pick = pick_index(humans.size());
        int bx = humans[pick].first;
        int by = humans[pick].second;

        //Human eaten (infected)
        delete city->getOrganism(bx, by);
        auto *spawn = new Zombie(city, 1);
        city->setOrganism(spawn, bx, by);
        spawn->setPosition(bx, by);
        spawn->setMoved(true);
        starveCounter = 0;
        breedCounter = 0;

        //For moving into empty squares
    } else if (!empties.empty() && humans.empty()) {
        size_t pick = pick_index(humans.size());
        int tx = empties[pick].first;
        int ty = empties[pick].second;

        //Move into empty square
        city->setOrganism(nullptr, ox, oy);
        city->setOrganism(this, tx, ty);
        setPosition(tx, ty);
        setMoved(true);
        starveCounter++;
        breedCounter++;

        //For no free spaces to move/no humans to eat
    } else {
        starveCounter++;
        breedCounter++;
    }


    //Starved conversion
    if (starveCounter >= ZOMBIE_STARVE) {
        int x = getX();
        int y = getY();
        auto *h = new Human(city, 1);
        city->setOrganism(h, x, y);
        h->setPosition(x, y);
        h->setMoved(true);
        delete this; //AI says to make sure that city step does not touch this after deletion

        return;
    }
};