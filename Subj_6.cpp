#include "Subj_6.h"

Subj_6::Subj_6(Tree* head, std::string name) : Tree(head, name, 6) {}

void Subj_6::signalRun(std::string& message){
    std::cout << "Signal from " << getAbsolutePath() << std::endl;
    message += " (class: 6)";
}

void Subj_6::handlerRun(std::string message){
    std::cout << "Signal to " << getAbsolutePath() << "   Text: " + message << std::endl;
}