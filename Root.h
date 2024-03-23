#ifndef __ROOT__H
#define __ROOT__H
#include "Tree.h"

class Root : public Tree {
public:
    Root(Tree*, std::string = "standard");
    void buildTree();
    int startApp();
};

#endif
