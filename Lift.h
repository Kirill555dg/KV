#ifndef __LIFT__H
#define __LIFT__H
#include "Tree.h"

const std::string liftName = "lift_object";

class Lift : public Tree {
    int capacity;
    int direction = 0; // -1: down, 0: stop, 1: up
    int currentFloor = 1;
    int currentFullness = 0;
public:
    Lift(Tree* tree, int capacity);
    int getCapacity();
    int getDirection();
    int getCurrentFloor();
    int getCurrentFullness();

    void handlerStatus(std::string message);
    void signalForFloorsStatus(std::string& message);

    void handlerCondition(std::string message);
    void signalOutput(std::string& message);

    void signalButton(std::string& message);
    void handlerToAddPassenger(std::string message);
    void handlerToRemovePassenger(std::string message);
    void handlerChangeDirection(std::string message);
    void handlerMove(std::string message);
};

#endif
