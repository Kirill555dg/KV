#include "Passenger.h"

Passenger::Passenger(Tree* tree, int start, int end, int tact, std::string name) : Tree(tree, name,7) {
    this -> start = start;
    this -> end = end;
    this -> tact = tact;
    if (start < end) {
        this -> direction = 1;
    } else {
        this -> direction = -1;
    }
}

int Passenger::getStart(){
    return start;
}

int Passenger::getEnd(){
    return end;
}

int Passenger::getDirection() {
    return direction;
}