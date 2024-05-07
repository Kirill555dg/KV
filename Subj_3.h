#ifndef __SUBJ_3__H
#define __SUBJ_3__H
#include "Tree.h"

class Subj_3 : public Tree {
public:
    Subj_3(Tree* tree, std::string name = "subj_3");
    void signalRun(std::string& message);
    void handlerRun(std::string message);
};


#endif
