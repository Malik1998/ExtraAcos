//
// Created by user on 26.11.18.
//

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"


Tree::Tree(std::string expression_) {
    expression = expression_;
    generateTree();
}

void Tree::generateTree() {
    head = new Node();

    size_t i = 0;
    i++;
    recursivelyBuild(i, head);
    i++;
}

void Tree::diriviate(std::string file_name) {
    std::ofstream file;
    file.open (file_name);


    Node* headDerivated = new Node;
    derviateRecursively(headDerivated, head, file);

    file << "\\documentclass[a4paper,10pt]{article}\n"
            "\\usepackage[utf8]{inputenc}\n"
            "\n"
            "\\usepackage[square,numbers]{natbib}\n"
            "\\bibliographystyle{unsrtnat}\n"
            "\n"
            "\\title{Derviation}\n"
            "\n"
            "\\begin{document}\n"
            "\n"
            "\\maketitle\n"
            "\n"
            "\n"
            "\n$";
    showTree(headDerivated, file);
    file <<"$";

    while(optimize(headDerivated)) {
        int ran = rand() % 7;
        if (ran < countWord) {
            file << " \\\\ " << Tree::strings[ran]  << " \\\\ ";
        } else {
            file << "=";
        }
        file <<"$";
        showTree(headDerivated, file);
        file <<"$";
    }

    file << "\n"
                         "\\medskip\n"
                         "\n"
                         "\n"
                         "\\end{document}";
    delete headDerivated;

    file.close();

    std::string command = ("pdflatex " + file_name);
    std::system(command.c_str());
}

Tree::TypeParse Tree::getTypeParse(char &i) {
    switch (i) {
        case 's':
        case 'c': {
            return function;
        }
        case '+':
        case '-':
        case '*':
        case '/': {
            return sign;
        }
        case 'x': {
            return variable;
        }
        case '(': {
            return open_bracket;
        }
        case ')': {
            return close_bracket;
        }
        default: {
            return const_number;
        }
    }
}

void Tree::recursivelyBuild(size_t &i, Node *pNode) {
    TypeParse typeParse = getTypeParse(expression[i]);
    switch (typeParse) {
        case variable: {
            Data data(Data::variable);
            pNode->setData(data);
            i++;
            return;
        }
        case open_bracket: {
            Node *newNode = new Node();
            newNode->setParent(pNode);

            i++; // open bracket
            recursivelyBuild(i, newNode);
            i++; // close bracket

            pNode->setLeft(newNode);

            if (i == expression.length() - 1) {
                return;
            }

            Data data;
            data.setType(getSign(i));
            pNode->setData(data);

            i++; // open bracket
            Node *leftNode = new Node();
            leftNode->setParent(pNode);
            recursivelyBuild(i, leftNode);

            pNode->setRight(leftNode);
            i++; //close bracket
            return;

        }
        case function: {


            Data data;
            data.setType(getFuncName(i));
            pNode->setData(data);

            i++; // open bracket

            Node *leftNode = new Node();
            leftNode->setParent(pNode);
            recursivelyBuild(i, leftNode);

            pNode->setLeft(leftNode);
            i++; //close bracket
            return;

        }
        case const_number: {
            Data data(Data::const_number);
            data.setNumber(getNumber(i));
            pNode->setData(data);
            return;
        }
    }
}

int Tree::getNumber(size_t &i) {
    int number = 0;
    while (expression[i] >= '0' && expression[i] <= '9') {
        number = number * 10 + (expression[i] - '0');
        i++;
    }
    return number;
}

Data::Type Tree::getSign(size_t &i) {
    char sign_parse = expression[i];
    i++;
    switch(sign_parse) {
        case '+':
            return Data::sign_plus;
        case '-':
            return Data::sign_mins;
        case '*':
            return Data::sign_mult;
        case '/':
            return Data::sign_div;
    }
}

Data::Type Tree::getFuncName(size_t &i) {
    char funct_parse = expression[i];
    i += 3;
    switch(funct_parse) {
        case 's':
            return Data::sin;
        case 'c':
            return Data::cos;
    }
}

//sin,
//cos,

void Tree::derviateRecursively(Node *d_curNode, Node *curNode, std::ofstream &cout) {
    switch (curNode->getData().getType()) {
        case Data::variable: {
            Data data(Data::const_number);
            data.setNumber(1);
            d_curNode->setData(data);
            return;
        }
        case Data::const_number: {
            Data data(Data::const_number);
            data.setNumber(0);
            d_curNode->setData(data);
            return;
        }
        case Data::sign_plus:
        case Data::sign_mins: {

            Data data(curNode->getData().getType());
            d_curNode->setData(data);

            Node *newNode = new Node();
            newNode->setParent(d_curNode);

            derviateRecursively(newNode, curNode->getLeft(), cout);

            d_curNode->setLeft(newNode);


            Node *newNodeRight = new Node();
            newNodeRight->setParent(d_curNode);

            derviateRecursively(newNodeRight, curNode->getRight(), cout);

            d_curNode->setRight(newNodeRight);
            return;

        }
        case Data::sign_mult: {

            Data data(Data::sign_plus);
            d_curNode->setData(data);

            make_mult_deriviative(d_curNode, curNode, cout);
            return;

        }
        case Data::sign_div: {
            Data data(Data::sign_div);
            d_curNode->setData(data);

            make_div_deriviative(d_curNode, curNode, cout);
            return;
        }
        case Data::sin: {
            Data data(Data::sign_mult);
            d_curNode->setData(data);

            Node *left = new Node(Data::cos);
            left->setParent(d_curNode);
            d_curNode->setLeft(left);

            Node *leftCopy = new Node(curNode->getLeft());
            left->setLeft(leftCopy);
            leftCopy->setParent(left);


            Node *right = new Node();
            right->setParent(d_curNode);
            d_curNode->setRight(right);

            derviateRecursively(right, curNode->getLeft(), cout);

            return;
        }
        case Data::cos: {
            Data data(Data::sign_mult);
            d_curNode->setData(data);

            Node *mainleft = new Node(Data::sign_mult);
            d_curNode->setLeft(mainleft);
            mainleft->setParent(d_curNode);

            Node *left = new Node(Data::sin);
            left->setParent(mainleft);
            mainleft->setLeft(left);

            Node *leftCopy = new Node(curNode->getLeft());
            left->setLeft(leftCopy);
            leftCopy->setParent(left);

            data = Data(Data::const_number);
            data.setNumber(-1);

            Node *right_left = new Node();
            right_left->setData(data);
            right_left->setParent(mainleft);
            mainleft->setRight(right_left);

            Node *right = new Node();
            right->setParent(d_curNode);
            d_curNode->setRight(right);

            derviateRecursively(right, curNode->getLeft(), cout);

            return;
        }
    }
}

void Tree::make_mult_deriviative(Node *d_curNode, Node *curNode, std::ofstream &cout) {

    Node *left = new Node(Data::sign_mult);
    left->setParent(d_curNode);
    d_curNode->setLeft(left);

    Node *d_new = new Node();
    derviateRecursively(d_new, curNode->getLeft(), cout);
    d_new->setParent(left);

    Node *copy = new Node(curNode->getRight());
    copy->setParent(left);

    left->setLeft(d_new);
    left->setRight(copy);


    Node *right = new Node(Data::sign_mult);
    right->setParent(d_curNode);
    d_curNode->setRight(right);

    d_new = new Node();
    derviateRecursively(d_new, curNode->getRight(), cout);
    d_new->setParent(right);

    copy = new Node(curNode->getLeft());
    copy->setParent(right);

    right->setLeft(d_new);
    right->setRight(copy);
}

void Tree::make_div_deriviative(Node *d_curNode, Node *curNode, std::ofstream &cout) {
    Node *left = new Node();
    left->setParent(d_curNode);
    d_curNode->setLeft(left);

    Data data(Data::sign_plus);
    left->setData(data);

    make_mult_deriviative(left, curNode, cout);


    Node *right = new Node(Data::sign_mult);
    right->setParent(d_curNode);

    d_curNode->setRight(right);

    Node *copyL = new Node(curNode->getRight());
    copyL->setParent(right);
    right->setLeft(copyL);


    Node *copyR = new Node(curNode->getRight());
    copyR->setParent(right);
    right->setRight(copyR);

}

void Tree::showTree(Node *curNode, std::ofstream &cout) {

    if(curNode == nullptr) {
        return;
    }

    if (curNode->getLeft() != nullptr) {
        if (curNode->getData().getType() == Data::sin || curNode->getData().getType() == Data::cos) {
            cout << curNode->getData().toString();
        }

        if (curNode->getData().getType() == Data::sign_div) {
            cout << "\\frac {";
        }


        cout << "( ";
        showTree(curNode->getLeft(), cout);
        cout << ")";
        if (curNode->getData().getType() == Data::sign_div) {
            cout << "}";
        }

    }

    if (!(curNode->getData().getType() == Data::sin || curNode->getData().getType() == Data::cos || curNode->getData().getType() == Data::sign_div)) {
        cout << curNode->getData().toString();
    }

    if (curNode->getRight() != nullptr) {
        if (curNode->getData().getType() == Data::sign_div) {
            cout << "{";
        }
        cout << "( ";
        showTree(curNode->getRight(), cout);
        cout << ")";
        if (curNode->getData().getType() == Data::sign_div) {
            cout << "}";
        }
    }
}

Tree::~Tree() {
    delete head;
}

bool Tree::optimize(Node *curNode) {

    if (curNode== nullptr) {
        return false;
    }
    switch (curNode->getData().getType()) {
        case Data::sign_plus:
        case Data::sign_mins: {
            if (curNode->getLeft() == nullptr) {
                Data data(Data::const_number);
                data.setNumber(0);
                curNode->setData(data);
                curNode->setLeft(nullptr);
                curNode->setRight(nullptr);
                return false;
            }
            if (canDelete(curNode->getLeft(), 0)) {
                delete curNode->getLeft();
                curNode->copy(curNode->getRight());
                return true;
            } else if (canDelete(curNode->getRight(), 0)) {
                delete curNode->getRight();
                curNode->copy(curNode->getLeft());
                return true;
            } else {
                return optimize(curNode->getLeft()) || optimize(curNode->getRight());
            }


        }
        case Data::sign_mult: {
            if (curNode->getLeft() == nullptr) {
                Data data(Data::const_number);
                data.setNumber(0);
                curNode->setLeft(nullptr);
                curNode->setRight(nullptr);
                curNode->setData(data);
                return false;
            }
            if (canDelete(curNode->getLeft(), 1)) {
                delete curNode->getLeft();
                curNode->copy(curNode->getRight());
                return true;
            } else if (canDelete(curNode->getRight(), 1)) {
                delete curNode->getRight();
                curNode->copy(curNode->getLeft());
                return true;
            } else {
                Data data1 = Data(Data::const_number);
                data1.setNumber(0);
                if (canDelete(curNode->getLeft(), 0) || canDelete(curNode->getRight(), 0)) {
                    delete curNode->getLeft();
                    delete curNode->getRight();
                    curNode->setData(data1);
                    curNode->setLeft(nullptr);
                    curNode->setRight(nullptr);
                    return true;
                }
                return optimize(curNode->getLeft()) || optimize(curNode->getRight());
            }


        }
        case Data::sign_div: {
            if (curNode->getLeft() == nullptr) {
                Data data(Data::const_number);
                data.setNumber(0);
                curNode->setLeft(nullptr);
                curNode->setRight(nullptr);
                curNode->setData(data);
                return false;
            }
            if (canDelete(curNode->getRight(), 1)) {
                delete curNode->getRight();
                curNode->copy(curNode->getLeft());
                return true;
            } else {
                Data data1 = Data(Data::const_number);
                data1.setNumber(0);
                if (canDelete(curNode->getLeft(), 0)) {
                    delete curNode->getLeft();
                    delete curNode->getRight();
                    curNode->setData(data1);
                    curNode->setLeft(nullptr);
                    curNode->setRight(nullptr);
                    return true;
                }
                return optimize(curNode->getLeft()) || optimize(curNode->getRight());
            }
        }

        case Data::sin:
        case Data::cos: {
            return optimize(curNode->getLeft());
        }
    }

    return false;
}

bool Tree::canDelete(Node *pNode, int value) {
    if (pNode == nullptr) {
        return true;
    }
    return pNode->getData().getType() == Data::const_number && pNode->getData().getNumber() == value;
}

