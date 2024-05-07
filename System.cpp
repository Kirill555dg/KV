#include "System.h"
#include "InputObject.h"
#include "OutputObject.h"
#include "Lift.h"
#include "Floor.h"
#include "Passenger.h"
#include "ControlPanel.h"

System::System(Tree* head) : Tree(head, systemName, 1) {}

void System::signalOutput(std::string& message){}

void System::signalTact(std::string& message){}


// Settings
void System::signalToGetSettings(std::string& message){}

void System::handlerFloorCount(std::string message){
    Tree* input = getSubject(inputObjectName);
    Tree* panel = getSubject(controlPanelName);
    Tree* output = getSubject(outputObjectName);

    int count = std::stoi(message);
    for (int i = 1; i <= count; i++) {
        Floor* floor = new Floor(this, i);
        floor -> setReadiness(1);
        if (i != count) floor -> connect(SIGNAL(Floor::signalButtonUp), panel, HANDLER(ControlPanel::handlerButtonUp));
        if (i != 1) floor -> connect(SIGNAL(Floor::signalButtonDown), panel, HANDLER(ControlPanel::handlerButtonDown));

        input -> connect(SIGNAL(InputObject::signalFloorCondition), floor, HANDLER(Floor::handlerCondition));
        floor -> connect(SIGNAL(Floor::signalOutput), output, HANDLER(OutputObject::handlerOutput));
        panel -> connect(SIGNAL(ControlPanel::signalToAddPassenger), floor, HANDLER(Floor::handlerToGivePassenger));
    }
}

void System::handlerLiftCapacity(std::string message){
    Tree* input = getSubject(inputObjectName);
    Tree* panel = getSubject(controlPanelName);
    Tree* output = getSubject(outputObjectName);

    int capacity = std::stoi(message);
    Lift* lift = new Lift(panel, capacity);
    lift -> setReadiness(1);

    lift -> connect(SIGNAL(Lift::signalButton), panel, HANDLER(ControlPanel::handlerLiftButton));
    panel -> connect(SIGNAL(ControlPanel::signalChangeDirection), lift, HANDLER(Lift::handlerChangeDirection));
    panel -> connect(SIGNAL(ControlPanel::signalToRemovePassenger), lift, HANDLER(Lift::handlerToRemovePassenger));
    panel -> connect(SIGNAL(ControlPanel::signalLiftMove), lift, HANDLER(Lift::handlerMove));

    input -> connect(SIGNAL(InputObject::signalLiftCondition), lift, HANDLER(Lift::handlerCondition));
    lift -> connect(SIGNAL(Lift::signalOutput), output, HANDLER(OutputObject::handlerOutput));

    this -> connect(SIGNAL(System::signalForLiftStatus), lift, HANDLER(Lift::handlerStatus));

    for (int i = 3; i < branch.size(); i++) { // Этажи в System начинаются с 3 индекса и идут до конца списка
        Floor* floor = (Floor*) branch[i];
        lift -> connect(SIGNAL(Lift::signalForFloorsStatus), floor, HANDLER(Floor::handlerStatus));
        floor -> connect(SIGNAL(Floor::signalToGivePassenger), lift, HANDLER(Lift::handlerToAddPassenger));
    }
}


// Commands
void System::signalToGetCommand(std::string& message){}

void System::handlerPassengerCondition(std::string message){
    Tree* object = getObjectOnTree(message);
    std::string outputMessage = "Passenger ";
    if (!object || object->num != 7) {
        outputMessage += message + " not found\n";
    } else {
        Passenger* passenger = (Passenger*) object;
        outputMessage += "condition: " + message;
        Tree* head = passenger -> getHead();
        if (head->num == 5) {
            outputMessage += " in the elevator\n";
        } else {
            outputMessage += " on the floor " + std::to_string(passenger->getStart()) + '\n';
        }
    }
    emitSignal(SIGNAL(System::signalOutput), outputMessage);
}

void System::handlerNewPassenger(std::string message){
    std::stringstream info(message);
    std::string word;
    info >> word;
    int start = std::stoi(word);
    info >> word;
    int end = std::stoi(word);
    std::string fullname;
    std::getline(info, fullname);
    fullname.erase(0, 1);

    for (int i = 3; i < branch.size(); i++) { // Этажи в System начинаются с 3 индекса и идут до конца списка
        Floor* floor = (Floor*) branch[i];
        if (floor->getLevel() == start) {
            Passenger* passenger = new Passenger(floor, start, end, tact, fullname);
            int direction = passenger->getDirection();
            if (direction == 1) {
                floor -> emitSignal(SIGNAL(Floor::signalButtonUp), message);
            } else {
                floor -> emitSignal(SIGNAL(Floor::signalButtonDown), message);
            }
            break;
        }
    }
}

void System::handlerSystemStatus(std::string message){
    message = std::to_string(tact) + ": ";
    emitSignal(SIGNAL(System::signalOutput), message);
    emitSignal(SIGNAL(System::signalForLiftStatus), message);
    message = "\n";
    emitSignal(SIGNAL(System::signalOutput), message);
}

void System::signalForLiftStatus(std::string& message){}

void System::handlerTurnOff(std::string message){
    isRunning = false;
    emitSignal(SIGNAL(System::signalOutput), message);
}

void System::handlerShowtree(std::string message){
    isRunning = false;
    printReadiness();
}


// Main methods
void System::build_tree_objects(){
    InputObject* input = new InputObject(this);
    ControlPanel* panel = new ControlPanel(this);
    OutputObject* output = new OutputObject(this);
    setReadinessOnBranch(1);

    this -> connect(SIGNAL(System::signalTact), panel, HANDLER(ControlPanel::handlerTact));
    this -> connect(SIGNAL(System::signalOutput), output, HANDLER(OutputObject::handlerOutput));

    this -> connect(SIGNAL(System::signalToGetSettings), input, HANDLER(InputObject::handlerSettingsInput));
    input -> connect(SIGNAL(InputObject::signalFloorCount), this, HANDLER(System::handlerFloorCount));
    input -> connect(SIGNAL(InputObject::signalLiftCapacity), this, HANDLER(System::handlerLiftCapacity));

    this -> connect(SIGNAL(System::signalToGetCommand), input, HANDLER(InputObject::handlerCommandInput));
    input -> connect(SIGNAL(InputObject::signalTurnOff), this, HANDLER(System::handlerTurnOff));
    input -> connect(SIGNAL(InputObject::signalShowtree), this, HANDLER(System::handlerShowtree));
    input -> connect(SIGNAL(InputObject::signalSystemStatus), this, HANDLER(System::handlerSystemStatus));
    input -> connect(SIGNAL(InputObject::signalPassengerCondition), this, HANDLER(System::handlerPassengerCondition));
    input -> connect(SIGNAL(InputObject::signalNewPassenger), this, HANDLER(System::handlerNewPassenger));

    std::string message{};
    this -> emitSignal(SIGNAL(System::signalToGetSettings), message);
    message = "Ready to work\n";
    this -> emitSignal(SIGNAL(System::signalOutput), message);
}

int System::exec_app() {
    std::string command{};
    this -> emitSignal(SIGNAL(System::signalToGetCommand), command);
    while (isRunning) {
        std::string message = "";
        this -> emitSignal(SIGNAL(System::signalTact), message);
        tact++;
        this -> emitSignal(SIGNAL(System::signalToGetCommand), command);
    }
    return 0;
}