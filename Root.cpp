#include "Root.h"
#include "Twig.h"
#include <iostream>

Root::Root(Tree* head, std::string name) : Tree(head, name) {}

void Root::buildTree(){
    std::string headName{}, subjName{}, prevSubjName{};

    std::cin >> headName;
    this -> rename(headName);
    Tree* head = this;
    std::cin >> headName >> subjName;
    while (headName != subjName) {
        if (head -> getName() == headName) {
            if (!head -> getSubject(subjName)) {
                Twig* newSubject = new Twig(head, subjName);
                prevSubjName = subjName;
            }
        } else if (head ->  getSubject(headName)){
            if (headName == prevSubjName) {
                head = head -> getSubject(headName);
                Twig* newSubject = new Twig(head, subjName);
                prevSubjName = subjName;
            }
        }
        std::cin >> headName >> subjName;
    }

}

int Root::startApp() {
    this -> printHierarchy(0);
    return 0;
}