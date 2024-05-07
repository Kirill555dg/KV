#ifndef __SUBJ_4__H
#define __SUBJ_4__H
#include "Tree.h"

class Subj_4 : public Tree {
public:
    Subj_4(Tree* tree, std::string name = "subj_4");
    void signalRun(std::string& message);
    void handlerRun(std::string message);
};


#endif
