#include "Root.h"
#include "Subj_2.h"
#include "Subj_3.h"
#include "Subj_4.h"
#include "Subj_5.h"
#include "Subj_6.h"


Root::Root(Tree* head, std::string name) : Tree(head, name, 1) {}

void Root::signalRun(std::string& message){
    std::cout << "Signal from " << getAbsolutePath() << std::endl;
    message += " (class: 1)";
}

void Root::handlerRun(std::string message){
    std::cout << "Signal to " << getAbsolutePath() << " Text: " + message << std::endl;
}

void Root::buildTree(){
    int number;
    std::string headName, subjName, headPath;
    std::cin >> headName;
    rename(headName);
    Tree* head = this;
    while (std::cin >> headPath && headPath != "endtree") {
        std::cin >> subjName >> number;
        head = head -> getObjectByPath(headPath);
        if (!head) {
            std::cout << "Object tree\n";
            printHierarchy();
            std::cout << "The head object " << headPath << " is not found\n";
            exit(1);
        }
        if (head -> getSubject(subjName)) {
            std::cout << headPath << "     Dubbing the names of subordinate objects\n";
        } else {
            if (number == 2) {
                new Subj_2(head, subjName);
            } else if (number == 3) {
                new Subj_3(head, subjName);
            }else if (number == 4) {
                new Subj_4(head, subjName);
            }else if (number == 5) {
                new Subj_5(head, subjName);
            }else if (number == 6) {
                new Subj_6(head, subjName);
            }
        }
    }

    std::string emitterPath, targetPath;

    Signal signals[]
            {
                    SIGNAL(Root::signalRun),
                    SIGNAL(Subj_2::signalRun),
                    SIGNAL(Subj_3::signalRun),
                    SIGNAL(Subj_4::signalRun),
                    SIGNAL(Subj_5::signalRun),
                    SIGNAL(Subj_6::signalRun)
            };

    Handler handlers[]
            {
                    HANDLER(Root::handlerRun),
                    HANDLER(Subj_2::handlerRun),
                    HANDLER(Subj_3::handlerRun),
                    HANDLER(Subj_4::handlerRun),
                    HANDLER(Subj_5::handlerRun),
                    HANDLER(Subj_6::handlerRun)
            };

    while (std::cin >> emitterPath && emitterPath != "end_of_connections"){
        std::cin >> targetPath;
        Tree* emitter = getObjectByPath(emitterPath);
        Tree* target = getObjectByPath(targetPath);
        if (emitter && target){
            emitter->connect(signals[emitter->num-1], target, handlers[target->num-1]);
        }
    }
}

int Root::startApp() {
    std::cout << "Object tree\n";
    printHierarchy();
    setReadinessOnBranch(1);

    std::string command, pathTarget, pathObject, message;
    int status;

    Signal signals[]
            {
                    SIGNAL(Root::signalRun),
                    SIGNAL(Subj_2::signalRun),
                    SIGNAL(Subj_3::signalRun),
                    SIGNAL(Subj_4::signalRun),
                    SIGNAL(Subj_5::signalRun),
                    SIGNAL(Subj_6::signalRun)
            };

    Handler handlers[]
            {
                    HANDLER(Root::handlerRun),
                    HANDLER(Subj_2::handlerRun),
                    HANDLER(Subj_3::handlerRun),
                    HANDLER(Subj_4::handlerRun),
                    HANDLER(Subj_5::handlerRun),
                    HANDLER(Subj_6::handlerRun)
            };

    while (std::cin >> command && command != "END") {
        if (command == "EMIT") {
            std::cin >> pathObject;
            std::getline(std::cin, message);
            Tree* object = getObjectByPath(pathObject);
            if (object){
                object -> emitSignal(signals[object->num-1], message);
            }
        } else if (command == "SET_CONNECT") {
            std::cin >> pathObject >> pathTarget;
            Tree* object = getObjectByPath(pathObject);
            Tree* target = getObjectByPath(pathTarget);
            if (object && target) {
                object -> connect(signals[object->num-1], target, handlers[target->num-1]);
            }
        } else if (command == "DELETE_CONNECT") {
            std::cin >> pathObject >> pathTarget;
            Tree* object = getObjectByPath(pathObject);
            Tree* target = getObjectByPath(pathTarget);
            if (object && target) {
                object -> disconnect(signals[object->num-1], target, handlers[target->num-1]);
            }
        } else if (command == "SET_CONDITION") {
            std::cin >> pathObject >> status;
            Tree* object = getObjectByPath(pathObject);
            if (object){
                object -> setReadiness(status);
            }
        }
    }
    return 0;
}