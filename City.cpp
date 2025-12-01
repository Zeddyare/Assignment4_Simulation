//
// Created by zdrol on 2025-11-25.
//

#include "lib/City.h"

//Default Constructor
City() {

};
//Virtual destuctor
~City() {

};

//Get location in the city for an organism
Organism *getOrganism( int x, int y ) {

};
//Set location in the city of an organism
void setOrganism( Organism *organism, int x, int y ) {

};

//What happens on a step/turn
void step() {

}; //includes all actions except reset, counting, and printing in this solution.

//Resets the city
void reset() {

};

//Gets type count for char
int countType(char) {
    for (int i =0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (City[i][j] = human) {
                humanCt++;
            } else if (City[i][j] == zombie) {
                zombieCt++;
            }
        }
        cout << endl;
    }
};
//Overrides cout << operator for city object
ostream& operator<<( ostream &output, City &city ) {
    for (int i =0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (City[i][j] = human) {
                cout << "H";
            } else if (City[i][j] == zombie) {
                cout << "Z";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
};

//Color settings
void col(int c) {

};