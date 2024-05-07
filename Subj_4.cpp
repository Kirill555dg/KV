#include "Subj_4.h"

Subj_4::Subj_4(Tree* head, std::string name) : Tree(head, name, 4) {}

void Subj_4::signalRun(std::string& message){
    std::cout << "Signal from " << getAbsolutePath() << std::endl;
    message += " (class: 4)";
}

void Subj_4::handlerRun(std::string message){
    std::cout << "Signal to " << getAbsolutePath() << "   Text: " + message << std::endl;
}