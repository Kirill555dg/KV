#ifndef __INPUTOBJECT__H
#define __INPUTOBJECT__H
#include "Tree.h"

const std::string inputObjectName = "input_object";

class InputObject : public Tree {
public:
    InputObject(Tree* tree);

    // Settings handler and signals
    void handlerSettingsInput(std::string message);

    void signalFloorCount(std::string& message);
    void signalLiftCapacity(std::string& message);

    // Command handler and signals
    void handlerCommandInput(std::string message);

    void signalNewPassenger(std::string& message);
    void signalPassengerCondition(std::string& message);
    void signalLiftCondition(std::string& message);
    void signalFloorCondition(std::string& message);
    void signalSystemStatus(std::string& message);
    void signalTurnOff(std::string& message);
    void signalShowtree(std::string& message);
};

#endif
