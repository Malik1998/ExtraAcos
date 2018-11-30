#include <iostream>
#include "Tree/Tree.h"

int main() {
    Tree tree("((5)+(3))");
    tree.diriviate("answ/five_plus_three.tex");

    Tree tree1("(sin((5)*((3)*(x)))+(3))");
    tree1.diriviate("answ/sinmult.tex");

    Tree tree2("((5)/(3))");
    tree2.diriviate("answ/divide.tex");

    Tree tree3("((x)+(3))");
    tree3.diriviate("answ/optim.tex");

    Tree tree4("((sin((x)+(3)))*(cos(x)))");
    tree4.diriviate("answ/optim2.tex");

    Tree tree5("(((sin((x)+(3)))*(cos(x)))/(cos(x)))");
    tree5.diriviate("answ/optim3.tex");

    Tree tree6("(((sin((x)*(5)))*(cos(sin((x)*(5)))))/((sin((x)*(5)))*(cos(sin((x)*(5))))))");
    tree6.diriviate("answ/optim4.tex");

}
