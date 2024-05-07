#ifndef __SUBJ_5__H
#define __SUBJ_5__H
#include "Tree.h"

class Subj_5 : public Tree {
public:
    Subj_5(Tree* tree, std::string name = "subj_5");
    void signalRun(std::string& message);
    void handlerRun(std::string message);
};


#endif
