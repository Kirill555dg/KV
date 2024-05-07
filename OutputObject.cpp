#include "OutputObject.h"

OutputObject::OutputObject(Tree* tree) : Tree(tree,outputObjectName,3) {}

void OutputObject::handlerOutput(std::string message){
    std::cout << message;
}