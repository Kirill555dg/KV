#ifndef __OUTPUTOBJECT__H
#define __OUTPUTOBJECT__H
#include "Tree.h"

const std::string outputObjectName = "output_object";

class OutputObject : public Tree {
public:
    OutputObject(Tree* tree);

    void handlerOutput(std::string message);
};

#endif
