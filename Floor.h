#ifndef __FLOOR__H
#define __FLOOR__H
#include "Tree.h"


const std::string floorName = "floor_object";

class Floor : public Tree {
    int level;
public:
    Floor(Tree* tree, int level);
    int getLevel();

    void handlerStatus(std::string message);

    void handlerCondition(std::string message);
    void signalOutput(std::string& message);

    void signalButtonDown(std::string& message);
    void signalButtonUp(std::string& message);

    void handlerToGivePassenger(std::string message);
    void signalToGivePassenger(std::string& message);
};

#endif
