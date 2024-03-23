#ifndef __TWIG__H
#define __TWIG__H
#include "Tree.h"

class Twig : public Tree {
public:
    Twig(Tree* tree, std::string name = "twig");
};

#endif
