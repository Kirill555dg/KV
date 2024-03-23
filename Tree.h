#ifndef __TREE__H
#define __TREE__H
#include <string>
#include <vector>

class Tree{
private:
    std::string name;
    Tree* head;
    std::vector<Tree*> branch;
public:
    Tree(Tree*, std::string = "standard");
    ~Tree();
    bool rename(std::string);
    std::string getName();
    Tree* getHead();
    Tree* getSubject(std::string);
    void printBranches();
};

#endif
