#include "Subj_2.h"

Subj_2::Subj_2(Tree* head, std::string name) : Tree(head, name, 2) {
}

void Subj_2::signalRun(std::string& message) {
    std::cout << "Signal from " << getAbsolutePath() << std::endl;
    message += " (class: 2)";
}

void Subj_2::handlerRun(std::string message){
    std::cout << "Signal to " << getAbsolutePath() << "   Text: " + message << std::endl;
}