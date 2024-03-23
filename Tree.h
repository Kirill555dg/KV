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
    Tree(Tree* tree, std::string name = "default");
    ~Tree();
    bool rename(std::string name);
    std::string getName();
    Tree* getHead();
    Tree* getSubject(std::string name);
    void printBranches();
};

#endif
