#include "Lift.h"
#include "Passenger.h"

Lift::Lift(Tree* tree, int capacity) : Tree(tree, liftName, 5) {
    this->capacity = capacity;
}

int Lift::getCapacity() {
    return capacity;
}

int Lift::getDirection() {
    return direction;
}

int Lift::getCurrentFloor() {
    return currentFloor;
}

int Lift::getCurrentFullness() {
    return currentFullness;
}



void Lift::handlerStatus(std::string message){
    message = "Elevator: " + std::to_string(currentFloor) + " " + std::to_string(currentFullness) + "  Floors:";
    emitSignal(SIGNAL(Lift::signalOutput), message);
    emitSignal(SIGNAL(Lift::signalForFloorsStatus), message);
}

void Lift::signalForFloorsStatus(std::string& message){}

void Lift::handlerCondition(std::string message){
    message = "Elevator condition: " + std::to_string(currentFloor) + " " + std::to_string(currentFullness);
    if (direction == 0 || direction == 2) {
        message += " stop\n";
    } else {
        message += " direction ";
        if (direction == 1) {
            message += "up\n";
        } else {
            message += "down\n";
        }
    }
    emitSignal(SIGNAL(Lift::signalOutput), message);
}

void Lift::signalOutput(std::string& message){}


void Lift::signalButton(std::string& message){

}

void Lift::handlerToAddPassenger(std::string message){
    Passenger* passenger = (Passenger*) getObjectByPath(message);
    passenger->changeHead(this);
    currentFullness++;
    // Если меньше 0 - лифт двигается вниз, если больше 0 - лифт двигается вверх
    int end = passenger->getEnd()*passenger->getDirection();
    message = std::to_string(end);
    emitSignal(SIGNAL(Lift::signalButton), message);
}

void Lift::handlerToRemovePassenger(std::string message){
    int i = 0;
    while (i < currentFullness) {
        Passenger* passenger = (Passenger*) branch[i];
        if (passenger->getEnd() == currentFloor) {
            branch.erase(branch.begin() + i);
            delete passenger;
            currentFullness--;
        } else {
            i++;
        }
    }
}

void Lift::handlerChangeDirection(std::string message){
    if (message == "-") {
        direction = 2;
    } else {
        int num = std::stoi(message);
        if (num > 0) {
            direction = 1;
        } else if (num < 0) {
            direction = -1;
        } else {
            direction = 0;
        }
    }
}

void Lift::handlerMove(std::string message){
    int target = abs(std::stoi(message));
    currentFloor += direction;
    if (currentFloor == target) {
        direction = 0;
    }
}