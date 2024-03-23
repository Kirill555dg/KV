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

Tree* Tree::getSubjectOnBranch(std::string name){

}

Tree* Tree::getSubjectOnTree(std::string name){

}

void Tree::printHierarchy(int level){
    for (int i = 0; i < level; i++) std::cout << "\t";
    std::cout << name << std::endl;
    level++;
    for (int i = 0; i < branch.size(); i++) {
        branch[i] -> printHierarchy(level);
    }
}

void Tree::printReadiness(int level){
    for (int i = 0; i < level; i++) std::cout << "\t";
    std::cout << name;
    if (readiness) std::cout << " is ready";
    else std::cout << " is not ready";
    level++;
    for (int i = 0; i < branch.size(); i++) {
        branch[i] -> printReadiness(level);
    }
}

void Tree::setReadiness(int status){
    readiness = status!=0;
}
