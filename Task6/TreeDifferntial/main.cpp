#include <iostream>
#include "Tree/Tree.h"

int main() {
    Tree tree("((5)+(3))");
    tree.diriviate("five_plus_three.tex");

    Tree tree1("(sin((5)*((3)*(x)))+(3))");
    tree1.diriviate("sinmult.tex");

    Tree tree2("((5)/(3))");
    tree2.diriviate("divide.tex");

    Tree tree3("((x)+(3))");
    tree3.diriviate("optim.tex");

    Tree tree4("((sin((x)+(3)))*(cos(x)))");
    tree4.diriviate("optim2.tex");
}