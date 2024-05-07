#include "Subj_5.h"

Subj_5::Subj_5(Tree* head, std::string name) : Tree(head, name, 5) {}

void Subj_5::signalRun(std::string& message){
    std::cout << "Signal from " << getAbsolutePath() << std::endl;
    message += " (class: 5)";
}

void Subj_5::handlerRun(std::string message){
    std::cout << "Signal to " << getAbsolutePath() << "   Text: " + message << std::endl;
}