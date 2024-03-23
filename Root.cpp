#include "Root.h"
#include <iostream>
#include <utility>

Root::Root(Tree* head, std::string name) : Tree(head, name) {}

void Root::buildTree(){
    std::string headName{}, subjName{}, prevSubjName{};

    std::cin >> headName;
    this -> rename(headName);
    Tree* head = this;

    std::cin >> headName >> subjName;
    while (headName != subjName) {
        if (head -> getName() == headName) {
            if (!head -> getSubject(subjName)){
                Tree* newSubject = new Tree(head, subjName);
                prevSubjName = subjName;
            }
        } else if (head -> getSubject(headName)){
            if (headName == prevSubjName) {
                head = head -> getSubject(headName);
                Tree* newSubject = new Tree(head, subjName);
                prevSubjName = subjName;
            }
        }
        std::cin >> headName >> subjName;
    }
}

int Root::startApp() {
    std::cout << this -> getName();
    this -> printBranches();
    return 0;
}