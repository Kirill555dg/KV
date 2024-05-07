#include "InputObject.h"

InputObject::InputObject(Tree* tree) : Tree(tree,inputObjectName,2) {}

void InputObject::handlerSettingsInput(std::string message){
    while (std::getline(std::cin, message) && message != "End of settings") {
        std::string num;
        std::stringstream input(message);
        input >> num;
        emitSignal(SIGNAL(InputObject::signalFloorCount), num);
        input >> num;
        emitSignal(SIGNAL(InputObject::signalLiftCapacity), num);
    }
}

void InputObject::signalFloorCount(std::string& message){}

void InputObject::signalLiftCapacity(std::string& message){}

void InputObject::handlerCommandInput(std::string message){
    std::getline(std::cin, message);
    if (message == "Elevator condition") {
        emitSignal(SIGNAL(InputObject::signalLiftCondition), message);
    } else if (message == "System status") {
        emitSignal(SIGNAL(InputObject::signalSystemStatus), message);
    } else if (message == "Turn off the system") {
        emitSignal(SIGNAL(InputObject::signalTurnOff), message);
    } else if (message == "SHOWTREE") {
        emitSignal(SIGNAL(InputObject::signalShowtree), message);
    } else {
        std::stringstream input(message);
        std::string word;
        input >> word;
        if (word == "Passenger") {
            input >> word;
            if (word == "condition") {
                input >> word;
                message = word;
                input >> word;
                message += " " + word;
                emitSignal(SIGNAL(InputObject::signalPassengerCondition), message);
            } else {
                message = word;
                input >> word;
                message += " " + word;
                std::getline(input, word);
                message += word;
                emitSignal(SIGNAL(InputObject::signalNewPassenger), message);
            }
        } else if (word == "Condition") {
            input >> message >> message >> message >> message;
            emitSignal(SIGNAL(InputObject::signalFloorCondition), message);
        }
    }
}

void InputObject::signalPassengerCondition(std::string& message){}

void InputObject::signalNewPassenger(std::string& message){}

void InputObject::signalLiftCondition(std::string& message){}

void InputObject::signalFloorCondition(std::string& message){}

void InputObject::signalSystemStatus(std::string& message){}

void InputObject::signalTurnOff(std::string& message){}

void InputObject::signalShowtree(std::string& message){}