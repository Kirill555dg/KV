#ifndef __CONTROLPANEL__H
#define __CONTROLPANEL__H
#include "Tree.h"

const std::string controlPanelName = "control_panel";

class ControlPanel : public Tree {
    std::vector<int> query;
    std::vector<int> ending;
public:
    ControlPanel(Tree* tree);

    void handlerButtonUp(std::string message);
    void handlerButtonDown(std::string message);
    void handlerLiftButton(std::string message);

    void handlerTact(std::string message);
    void signalToAddPassenger(std::string& message);
    void signalToRemovePassenger(std::string& message);
    void signalChangeDirection(std::string& message);
    void signalLiftMove(std::string& message);
};

#endif
