#include "ControlPanel.h"
#include "Lift.h"

ControlPanel::ControlPanel(Tree* tree) : Tree(tree, controlPanelName, 4) {}

void ControlPanel::handlerButtonUp(std::string message) {
    query.push_back(std::stoi(message));
}

void ControlPanel::handlerButtonDown(std::string message) {
    query.push_back(-1*std::stoi(message));
}

void ControlPanel::handlerLiftButton(std::string message) {
    int end = std::stoi(message);
    auto position = std::lower_bound(ending.begin(), ending.end(), end);
    ending.insert(position, end); // В векторе ending первый элемент - ближайший этаж, на котором нужно выйти
}

void ControlPanel::handlerTact(std::string message){
    Lift* lift = (Lift*) getSubject(liftName);
    int curDir = lift->getDirection();
    int curFloor = lift->getCurrentFloor();
    if (lift->getCurrentFullness() == 0) {
        if (query.empty()) return;
        int target = abs(query[0]);
        message = std::to_string(query[0]);
        if (curDir == 0) { // Лифт стоит (либо достиг этажа первого пассажира, либо не начал движение)
            if (target == curFloor) { // Лифт достиг этажа первого пассажира
                // Добавление первого пассажира
                emitSignal(SIGNAL(ControlPanel::signalToAddPassenger), message);
                query.erase(query.begin());
            } else { // Лифт не начал движение
                std::string dirMessage = std::to_string(target-curFloor); // Указание направления движения лифта
                emitSignal(SIGNAL(ControlPanel::signalChangeDirection), dirMessage);
                emitSignal(SIGNAL(ControlPanel::signalLiftMove), message);
            }
        } else { // Лифт должен безостановочно двигаться до этажа первого пассажира
            emitSignal(SIGNAL(ControlPanel::signalLiftMove), message);
        }
    }
    if (lift->getCurrentFullness() != 0) { // В лифте есть пассажиры (или появился первый)
        if (curDir == 0) { // Лифт стоит, значит высадка и/или посадка пассажира(-ов)

            // Высадка пассажиров из лифта
            while (!ending.empty()) {
                if (abs(ending[0]) == curFloor) {
                    emitSignal(SIGNAL(ControlPanel::signalToRemovePassenger), message);
                    ending.erase(ending.begin());
                } else {
                    break;
                }
            }


            // Добавление подходящих пассажиров, находящихся на этаже
            int i = 0;
            while (i < query.size() && lift->getCurrentFullness() < lift->getCapacity()) {
                // Если лифт едет вниз, то будет "-" * "-" = "+"
                // Если лифт едет вверх, то будет "+" * "+" = "+"
                if (curFloor == abs(query[i]) && (ending.empty() || query[i]*ending[0] > 0)) { // Если лифт пуст или совпадает направление
                    message = std::to_string(query[i]);
                    emitSignal(SIGNAL(ControlPanel::signalToAddPassenger), message);
                    query.erase(query.begin() + i);
                } else {
                    i++;
                }
            }
            if (!ending.empty()) { // Если лифт не пуст
                message = std::to_string(ending[0]); // Движение к ближайшему этажу выхода
            } else if (!query.empty()) { // Если есть запрос
                message = std::to_string(abs(query[0])-curFloor); // Движение к новому первому пассажиру
            } else { // Лифт стоит
                message = "0";
            }
            emitSignal(SIGNAL(ControlPanel::signalChangeDirection), message);
        } else { // Лифт движется
            int targetFloor = ending[0];
            for (int i = 0; i < query.size(); i++) {
                if (curDir*curFloor < query[i] && query[i] < targetFloor) {
                    targetFloor = query[i];
                }
            }
            message = std::to_string(targetFloor);
            emitSignal(SIGNAL(ControlPanel::signalLiftMove), message);
        }
    }
}

void ControlPanel::signalToAddPassenger(std::string& message) {}

void ControlPanel::signalToRemovePassenger(std::string& message) {}

void ControlPanel::signalChangeDirection(std::string& message){}

void ControlPanel::signalLiftMove(std::string& message) {}
