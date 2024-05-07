#ifndef __TREE__H
#define __TREE__H
#include <string>
#include <vector>
#include <iostream>

class Tree{
public:
    const int num;
    Tree(Tree* tree, std::string name = "default", int num = 0);
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
    Tree* getObjectByPath(std::string path);

    // Новые методы в КВ4
    typedef void (Tree:: *Signal) (std::string&); //Указатель на метод сигнала
    typedef void (Tree:: *Handler) (std::string); //Указатель на метод обработчика

    void connect(Signal signal, Tree* target, Handler handler);
    void disconnect(Signal signal, Tree* target, Handler handler);
    void emitSignal(Signal signal, std::string& message);
    std::string getAbsolutePath();
    void setReadinessOnBranch(int status);
private:
    std::string name;
    Tree* head;
    std::vector<Tree*> branch;
    // Новое поле
    int readiness = 0;
    struct Connection{
        Signal signal;
        Tree* target;
        Handler handler;
        Connection(Signal signal, Tree* target, Handler handler);
    };
    std::vector<Connection*> connections;
};

#define SIGNAL(s_func) (Signal) (&s_func)
#define HANDLER(h_func) (Handler) (&h_func)

#endif
