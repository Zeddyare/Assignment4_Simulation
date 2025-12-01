//
// Created by zdrol on 2025-11-25.
//

#include "lib/Organism.h"

//Default constructor for organisms
Organism() {

};

//Constructor for organism within city
Organism( City *city, int size) {

};

//Oragnism virtual destructor
~Organism() {

};

//Abstract turn method for Organism (Overridden by human and zombie)
//Ensure moved property changes to true so they only move once per turn
virtual void turn() = 0 {

};

//cout << operator override for organism
ostream& operator<<( ostream &output, Organism *organism ) {

};