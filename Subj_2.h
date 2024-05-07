#ifndef __SUBJ_2__H
#define __SUBJ_2__H
#include "Tree.h"

class Subj_2 : public Tree {
public:
    Subj_2(Tree* tree, std::string name = "subj_2");
    void signalRun(std::string& message);
    void handlerRun(std::string message);
};

#endif
