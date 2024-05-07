#include "Floor.h"
#include "Passenger.h"

Floor::Floor(Tree* tree, int level) : Tree(tree, floorName + "_" + std::to_string(level),6) {
    this->level = level;
}

int Floor::getLevel() {
    return level;
}

void Floor::handlerStatus(std::string message){
    int len = branch.size();
    if (len == 0) return;
    int up = 0, down = 0;
    for (int i = 0; i < len; i++) {
        Passenger* passenger = (Passenger*) branch[i];
        if (passenger->getDirection() == 1) {
            up++;
        } else {
            down++;
        }
    }
    message = " (" + std::to_string(level) + ": " + std::to_string(up) + "-" + std::to_string(down) + ")";
    emitSignal(SIGNAL(Floor::signalOutput), message);
}

void Floor::handlerCondition(std::string message){
    if (std::stoi(message) != level) {
        return;
    }
    std::string messageUp = "Condition on the floor " + message + " -up-";
    std::string messageDown = "Condition on the floor " + message + " -down-";
    for (int i = 0; i < branch.size(); i++) {
        Passenger* passenger = (Passenger*) branch[i];
        if (passenger->getDirection() == 1) {
            messageUp += "  " + passenger->getName();
        } else {
            messageDown += "  " + passenger->getName();
        }
    }
    messageUp += '\n';
    messageDown += '\n';
    emitSignal(SIGNAL(Floor::signalOutput), messageUp);
    emitSignal(SIGNAL(Floor::signalOutput), messageDown);
}

void Floor::signalOutput(std::string& message){}

void Floor::signalButtonDown(std::string& message){
    message = std::to_string(level);
}

void Floor::signalButtonUp(std::string& message){
    message = std::to_string(level);
}

void Floor::handlerToGivePassenger(std::string message) {
    int target = std::stoi(message);
    if (abs(target) != level) {
        return;
    }
    for (int i = 0; i < branch.size(); i++) {
        Passenger* passenger = (Passenger*) branch[i];
        if (passenger->getStart()*passenger->getDirection() == target) {
            message = passenger->getAbsolutePath();
            emitSignal(SIGNAL(Floor::signalToGivePassenger), message);
            return;
        }
    }
}

void Floor::signalToGivePassenger(std::string& message) {}