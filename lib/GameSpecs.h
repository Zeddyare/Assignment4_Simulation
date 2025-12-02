#ifndef _GAMESPECS_H
#define _GAMESPECS_H


const int GRIDSIZE = 20; // size of the square grid
const int HUMAN_STARTCOUNT = 100; // initial Human count
const int ZOMBIE_STARTCOUNT = 5; // initial Zombie count
const int BUILDING_COUNT = 5;
const int HUMAN_BREED = 3; // steps until a Human breeds
const int ZOMBIE_BREED = 8; // steps until a Zombie breeds
const int ZOMBIE_STARVE = 3; // steps until a Zombie starves and converts back
const int BUILDING_MAX = 2; //Number of humans one building can host
const char HUMAN_CH = 72;//72 "H"// ascii for Human
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char BUILDING_CH = 35; // "#" ascii for hash/pound
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const int INTERVAL = 300; // millisecond pause between city steps
const int ITERATIONS = 1000; // max number of steps

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquoise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 3; // turquoise
const int ZOMBIE_COLOR = 14; // bright yellow
const int DASH_COLOR = 8; // pale white
const int BUILDING_COLOR = 10; // bright green

#endif