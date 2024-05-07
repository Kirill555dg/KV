#include "Subj_3.h"

Subj_3::Subj_3(Tree* head, std::string name) : Tree(head, name, 3) {
}

void Subj_3::signalRun(std::string& message){
    std::cout << "Signal from " << getAbsolutePath() << std::endl;
    message += " (class: 3)";
}

void Subj_3::handlerRun(std::string message){
    std::cout << "Signal to " << getAbsolutePath() << "   Text: " + message << std::endl;
}