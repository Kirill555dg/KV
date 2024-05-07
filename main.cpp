#include "System.h"

int main()
{
    System system (nullptr);
    system.build_tree_objects();
    return system.exec_app();
}
