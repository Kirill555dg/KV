#include "Tree.h"
#include <iostream>

Tree::Tree(Tree* head, std::string name){
    this -> head = head;
    this -> name = name;
    if ( head ) head -> branch.push_back( this );
}


Tree::~Tree(){
    for (int i = 0; i < branch.size(); i++){
        delete branch[i];
    }
}

bool Tree::rename(std::string name){
    if (head && head -> getSubject(name)) {
        return false;
    }
    this -> name = name;
    return true;
}

void Tree::printBranches(){
    if (!branch.empty()) {
        std::cout << std::endl << name;
        for (int i = 0; i < branch.size(); i++) {
            std::cout << "  " << branch[i] -> getName();
        }
        branch.back() -> printBranches();
    }
}

Tree* Tree::getHead(){
    return head;
}

Tree* Tree::getSubject(std::string name){
    for (int i = 0; i < branch.size(); i++){
        if (branch[i] -> getName() == name)
            return branch[i];
    }
    return nullptr;
}

std::string Tree::getName(){
    return name;
}