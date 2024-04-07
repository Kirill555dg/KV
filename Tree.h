#ifndef __TREE__H
#define __TREE__H
#include <string>
#include <vector>

class Tree{
private:
    std::string name;
    Tree* head;
    std::vector<Tree*> branch;
    // Новое поле
    int readiness = 0;
public:
    Tree(Tree* tree, std::string name = "default");
    ~Tree();
    bool rename(std::string name);
    std::string getName();
    Tree* getHead();
    Tree* getSubject(std::string name);
    //void printBranches(); - устаревший метод
    // Новые методы в КВ2
    void printHierarchy();
    void printReadiness();
    Tree* getObjectOnBranch(std::string name);
    Tree* getObjectOnTree(std::string name);
    void setReadiness(int status);

    // Новые методы в КВ3
    bool changeHead(Tree* newHead);
    void deleteSubject(std::string name);
    Tree* getObject(std::string path);

    //УНИКАЛЬНОСТЬ
    int countOfObjects(std::string name);
};

#endif
