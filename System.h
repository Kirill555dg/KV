#ifndef __SYSTEM__H
#define __SYSTEM__H
#include "Tree.h"

const std::string systemName = "system_object";

class System : public Tree {
    int tact = 1;
    bool isRunning = true;
public:
    System(Tree* tree);

    void build_tree_objects();
    int exec_app();


    void signalOutput(std::string& message);
    void signalTact(std::string& message);

    // Settings signal and handlers
    void signalToGetSettings(std::string& message);

    void handlerFloorCount(std::string message);
    void handlerLiftCapacity(std::string message);

    // Command signal and handlers
    void signalToGetCommand(std::string& message);

    void handlerPassengerCondition(std::string message);
    void handlerNewPassenger(std::string message);

    void handlerSystemStatus(std::string message);
    void signalForLiftStatus(std::string& message);

    void handlerTurnOff(std::string message);
    void handlerShowtree(std::string message);
};

#endif
