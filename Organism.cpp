// cpp
#include "lib/Organism.h"
#include "lib/GameSpecs.h"

Organism::Organism()
    : x(0), y(0), size(1), moved(false), city(nullptr)
{}

Organism::Organism( City *city_, int size_)
    : x(0), y(0), size(size_), moved(false), city(city_)
{}

Organism::~Organism() {} //Overridden

int Organism::getX() const { return x; }
int Organism::getY() const { return y; }
void Organism::setPosition(int nx, int ny) { x = nx; y = ny; }

bool Organism::hasMoved() const { return moved; }
void Organism::setMoved(bool mv) { moved = mv; }

std::ostream& operator<<( std::ostream &output, Organism *organism )
{
    if (!organism) {
        output << SPACE_CH;
        return output;
    }
    output << organism->getChar();
    return output;
}
