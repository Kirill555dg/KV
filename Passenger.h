#ifndef __PASSENGER__H
#define __PASSENGER__H
#include "Tree.h"

class Passenger : public Tree {
    int start;
    int end;
    int direction; // -1: down, 1: up
    int tact;
public:
    Passenger(Tree* tree, int start, int end, int tact, std::string name = "passenger");

    int getStart();
    int getEnd();
    int getDirection();
};

#endif
