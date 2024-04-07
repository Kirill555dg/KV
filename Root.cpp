#include "Root.h"
#include "Subj_2.h"
#include "Subj_3.h"
#include "Subj_4.h"
#include "Subj_5.h"
#include "Subj_6.h"
#include <iostream>


Root::Root(Tree* head, std::string name) : Tree(head, name) {}

void Root::buildTree(){
    int number;
    std::string headName, subjName, headPath;
    std::cin >> headName;
    rename(headName);
    Tree* head = this;
    while (std::cin >> headPath && headPath != "endtree") {
        std::cin >> subjName >> number;
        head = head -> getObject(headPath);
        if (!head) {
            std::cout << "Object tree\n";
            printHierarchy();
            std::cout << "The head object " << headPath << " is not found";
            exit(1);
        }
        if (head -> getSubject(subjName)) {
            std::cout << headPath << "     Dubbing the names of subordinate objects";
        } else {
            switch (number) {
                case 2:
                    new Subj_2(head, subjName);
                    break;
                case 3:
                    new Subj_3(head, subjName);
                    break;
                case 4:
                    new Subj_4(head, subjName);
                    break;
                case 5:
                    new Subj_5(head, subjName);
                    break;
                case 6:
                    new Subj_6(head, subjName);
                    break;
                default:
                    break;
            }
        }
    }
}

int Root::startApp() {
    std::cout << "Object tree\n";
    printHierarchy();
    std::string command, target, path = "/";
    Tree* object = this;
    while (std::cin >> command && command != "END") {
        if (command == "SET") {
            std::cin >> path;
            Tree* newObject = object -> getObject(path);
            if (newObject) {
                object = newObject;
                std::cout << "Object is set: " << object->getName() << std::endl;
            } else {
                std::cout << "The object was not found at the specified coordinate: " << path << std::endl;
            }
        } else if (command == "FIND") {
            std::cin >> path;
            Tree* subject = object -> getObject(path);
            if (subject) {
                std::cout << path << "     Object name: " << subject -> getName() << std::endl;
            } else {
                std::cout << path << "     Object is not found\n";
            }
        } else if (command == "MOVE") {
            std::cin >> path;
            Tree* newHead = object -> getObject(path);
            if (!newHead) {
                std::cout << path << "     Head object is not found\n";
            } else if (newHead -> getSubject(object -> getName())) {
                std::cout << path << "     Dubbing the names of subordinate objects\n";
            } else if (!object -> changeHead(newHead)) {
                std::cout << path << "     Redefining the head object failed\n";
            } else {
                std::cout << "New head object: " << newHead -> getName() << std::endl;
            }
        } else if (command == "DELETE") {
            std::cin >> target;
            Tree* subject = object -> getSubject(target);
            if (subject) {
                std::string absolutePath = '/' + subject -> getName();
                while (subject -> getHead() != this) {
                    subject = subject -> getHead();
                    absolutePath = '/' + subject -> getName() + absolutePath;
                }
                object -> deleteSubject(target);
                std::cout << "The object " << absolutePath << " has been deleted" << std::endl;
            }
        }
    }
    std::cout << "Current object hierarchy tree\n";
    printHierarchy();
    return 0;
}