#include "Tree.h"
#include <iostream>
#include <functional>

Tree::Connection::Connection(Signal signal, Tree* target, Handler handler){
    this->signal = signal;
    this->target = target;
    this->handler = handler;
};

Tree::Tree(Tree* head, std::string name, int num) : num(num) {
    this -> head = head;
    this -> name = name;
    if ( head ) head -> branch.push_back( this );
}

Tree::~Tree(){
    for (int i = 0; i < branch.size(); i++){
        delete branch[i];
    }
}

bool Tree::rename(std::string name){
    if (head && head -> getSubject(name)) {
        return false;
    }
    this -> name = name;
    return true;
}
// устаревший метод
/*void Tree::printBranches(){
	if (!branch.empty()) {
		std::cout << std::endl << name;
		for (int i = 0; i < branch.size(); i++) {
			std::cout << "  " << branch[i] -> getName();
		}
		branch.back() -> printBranches();
	}
}*/

Tree* Tree::getHead(){
    return head;
}

Tree* Tree::getSubject(std::string name){
    for (int i = 0; i < branch.size(); i++){
        if (branch[i] -> getName() == name)
            return branch[i];
    }
    return nullptr;
}

std::string Tree::getName(){
    return name;
}

Tree* Tree::getObjectOnBranch(std::string name){
    std::function<int(std::string name, Tree* obj)> count = [&count](std::string name, Tree* obj){
        int cou = 0;
        if (obj -> getName() == name) cou++;
        for (int i = 0; i < obj -> branch.size(); i++) {
            cou += count(name, obj -> branch[i]);
        }
        return cou;
    };
    if (count(name, this) != 1) return nullptr;
    if (getName() == name) {
        return this;
    } else {
        for (int i = 0; i < branch.size(); i++) {
            Tree* object = branch[i] -> getObjectOnBranch(name);
            if (object) {
                return object;
            }
        }
    }
    return nullptr;
}

Tree* Tree::getObjectOnTree(std::string name){
    Tree* root = this;
    while (root -> getHead()) {
        root = root -> getHead();
    }
    return root -> getObjectOnBranch(name);
}

void Tree::printHierarchy(){
    Tree* root = getHead();
    while (root) {
        std::cout << "    ";
        root = root -> getHead();
    }
    std::cout << name << std::endl;
    for (int i = 0; i < branch.size(); i++) {
        branch[i] -> printHierarchy();
    }
}

void Tree::printReadiness(){
    Tree* root = getHead();
    while (root) {
        std::cout << "    ";
        root = root -> getHead();
    }
    std::cout << name;
    if (readiness) {
        std::cout << " is ready\n";
    } else {
        std::cout << " is not ready\n";
    }
    for (int i = 0; i < branch.size(); i++) {
        branch[i] -> printReadiness();
    }
}

void Tree::setReadiness(int status){
    if (status == 0) {
        readiness = 0;
        for (int i = 0; i < branch.size(); i++){
            branch[i] -> setReadiness(0);
        }
    } else {
        if (getHead() && getHead() -> readiness == 0) {
            readiness = 0;
        } else {
            readiness = status;
        }
    }
}

void Tree::setReadinessOnBranch(int status){
    setReadiness(status);
    for (int i = 0; i < branch.size(); i++){
        branch[i] -> setReadinessOnBranch(status);
    }
}

void Tree::deleteSubject(std::string name){
    Tree* subject = getSubject(name);
    if (subject) {
        for (int i = 0; i < branch.size(); i++) {
            if (branch[i] == subject) {
                branch.erase(branch.begin() + i);
                delete subject;
                break;
            }
        }
    }
}

Tree* Tree::getObjectByPath(std::string path){
    if (path.empty()) {
        return nullptr;
    }
    Tree* root = this;
    if (path[0] == '.') {
        if (path == ".") {
            return root;
        }
        path.erase(0,1);
        return root -> getObjectOnBranch(path);
    } else if (path[0] == '/') {
        while (root -> getHead()) {
            root = root -> getHead();
        }
        if (path == "/") {
            return root;
        }
        if (path[1] == '/') {
            path.erase(0, 2);
            return root -> getObjectOnTree(path);
        }
        path.erase(0, 1);
    }
    std::string curName{};
    for (int i = 0; i < path.length(); i++) {
        if (path[i] == '/') {
            root = root -> getSubject(curName);
            if (!root) return root;
            curName = "";
        } else {
            curName += path[i];
        }
    }
    return root -> getSubject(curName);
}

bool Tree::changeHead(Tree* newHead){
    if (!newHead) return false;
    if (!this -> head) return false;
    if (newHead -> getSubject(this -> getName())) return false;

    Tree* root = newHead;
    while (root) {
        if (root == this) return false;
        root = root -> getHead();
    }
    Tree* curHead = this -> head;
    for (int i = 0; i < curHead -> branch.size(); i++) {
        if (curHead -> branch[i] == this) {
            curHead -> branch.erase(curHead -> branch.begin() + i);
            break;
        }
    }
    this -> head = newHead;
    newHead -> branch.push_back(this);
    return true;
}

void Tree::connect(Signal signal, Tree* target, Handler handler){
    for (int i = 0; i < connections.size(); i++){

        if (connections[i]->signal == signal &&
            connections[i]->target == target &&
            connections[i]->handler == handler)
        {
            return;
        }
    }
    connections.push_back(new Connection(signal, target, handler));
}

void Tree::disconnect(Signal signal, Tree* target, Handler handler){
    for (int i = 0; i < connections.size(); i++){

        if (connections[i]->signal == signal &&
            connections[i]->target == target &&
            connections[i]->handler == handler)
        {
            connections.erase(connections.begin() + i);
            return;
        }
    }
}

void Tree::emitSignal(Signal signal, std::string& message){
    if (readiness == 0) return;

    Handler handler;
    Tree* target;

    (this ->* signal) (message);

    for (int i = 0; i < connections.size(); i++){
        if (connections[i]->signal == signal){
            handler = connections[i]->handler;
            target = connections[i]->target;
            if (target->readiness != 0){
                (target ->* handler) (message);
            }
        }
    }
}

std::string Tree::getAbsolutePath(){
    Tree* curHead = this->getHead();
    if (!curHead) {
        return "/";
    }
    std::string absolutePath = '/' + getName();
    while (curHead -> getHead()){
        absolutePath = '/' + curHead->getName() + absolutePath;
        curHead = curHead -> getHead();
    }
    return absolutePath;
}