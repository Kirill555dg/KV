#ifndef __ROOT__H
#define __ROOT__H
#include "Tree.h"

class Root : public Tree {
public:
    Root(Tree* tree, std::string name = "root");
    void buildTree();
    int startApp();

    void signalRun(std::string& message);
    void handlerRun(std::string message);
};

#endif
