#include <iostream>

#include "ScapegoatTree.h"

int main() {

    ScapegoatTree<int> tree;

    tree.printPretty();

    tree.insert(0);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);

    tree.printPretty();

    return 0;
}