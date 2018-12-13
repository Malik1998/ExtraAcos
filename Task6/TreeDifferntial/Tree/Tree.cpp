//
// Created by user on 26.11.18.
//

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "Tree.h"

#define VARIABLE_DATA Data data(Data::variable);
#define CONST_DATA Data data(Data::const_number);
#define PNODE_SET_DATA pNode->setData(data);
#define L getLeft()
#define R getRight()
#define DATA getData()
#define TYPE getType()
#define SET_L setLeft
#define SET_R setRight
#define CREATE_DATA Data data;
#define PRIOR getPriority()
#define NUMBER getNumber()
#define SET_NUMBER setNumber



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

    file << "\\documentclass[a4paper, 20pt]{article}\n"
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
            "\n";
    file << "( ";
    showTree(head, file);
    file << ")'" << " = \\\\ ";

    showTree(headDerivated, file);
    file <<"";

    while(optimize(headDerivated)) {
        int ran = rand() % 7;
        if (ran < countWord) {
            file << " \\\\ " << Tree::strings[ran]  << " \\\\ ";
        } else {
            file << " = \\\\ ";
        }
        file <<" ";
        showTree(headDerivated, file);
        file <<"  ";
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
            VARIABLE_DATA
            PNODE_SET_DATA
            i++;
            return;
        }
        case open_bracket: {
            Node *newNode = new Node();

            i++; // open bracket
            recursivelyBuild(i, newNode);
            i++; // close bracket

            pNode->SET_L(newNode);

            if (i == expression.length() - 1) {
                return;
            }

            CREATE_DATA
            data.setType(getSign(i));
            PNODE_SET_DATA

            i++; // open bracket
            Node *leftNode = new Node();
            recursivelyBuild(i, leftNode);

            pNode->SET_R(leftNode);
            i++; //close bracket
            return;

        }
        case function: {


            CREATE_DATA
            data.setType(getFuncName(i));
            PNODE_SET_DATA

            i++; // open bracket

            Node *leftNode = new Node();
            recursivelyBuild(i, leftNode);

            pNode->SET_L(leftNode);
            i++; //close bracket
            return;

        }
        case const_number: {
            CONST_DATA
            data.SET_NUMBER(getNumber(i));
            PNODE_SET_DATA
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

void Tree::derviateRecursively(Node *pNode, Node *curNode, std::ofstream &cout) {
    switch (curNode->DATA.TYPE) {
        case Data::variable: {
            CONST_DATA
            data.SET_NUMBER(1);
            PNODE_SET_DATA
            return;
        }
        case Data::const_number: {
            CONST_DATA
            data.SET_NUMBER(0);
            PNODE_SET_DATA
            return;
        }
        case Data::sign_plus:
        case Data::sign_mins: {

            Data data(curNode->DATA.TYPE);
            PNODE_SET_DATA

            Node *newNode = new Node();

            derviateRecursively(newNode, curNode->L, cout);

            pNode->SET_L(newNode);


            Node *newNodeRight = new Node();

            derviateRecursively(newNodeRight, curNode->R, cout);

            pNode->SET_R(newNodeRight);
            return;

        }
        case Data::sign_mult: {

            Data data(Data::sign_plus);
            PNODE_SET_DATA

            make_mult_deriviative(pNode, curNode, cout);
            return;

        }
        case Data::sign_div: {
            Data data(Data::sign_div);
            PNODE_SET_DATA

            make_div_derivative(pNode, curNode, cout);
            return;
        }
        case Data::sin: {
            Data data(Data::sign_mult);
            PNODE_SET_DATA

            Node *left = new Node(Data::cos);
            pNode->SET_L(left);

            Node *leftCopy = new Node(curNode->L);
            left->SET_L(leftCopy);


            Node *right = new Node();
            pNode->SET_R(right);

            derviateRecursively(right, curNode->L, cout);

            return;
        }
        case Data::cos: {
            Data data(Data::sign_mult);
            PNODE_SET_DATA

            Node *mainleft = new Node(Data::sign_mult);
            pNode->SET_L(mainleft);

            Node *left = new Node(Data::sin);
            mainleft->SET_L(left);

            Node *leftCopy = new Node(curNode->L);
            left->SET_L(leftCopy);

            data = Data(Data::const_number);
            data.SET_NUMBER(-1);

            Node *right_left = new Node();
            right_left->setData(data);
            mainleft->SET_R(right_left);

            Node *right = new Node();
            pNode->SET_R(right);

            derviateRecursively(right, curNode->L, cout);

            return;
        }
    }
}

void Tree::make_mult_deriviative(Node *d_curNode, Node *curNode, std::ofstream &cout) {

    Node *left = new Node(Data::sign_mult);
    d_curNode->SET_L(left);

    Node *d_new = new Node();
    derviateRecursively(d_new, curNode->L, cout);

    Node *copy = new Node(curNode->R);

    left->SET_L(d_new);
    left->SET_R(copy);


    Node *right = new Node(Data::sign_mult);
    d_curNode->SET_R(right);

    d_new = new Node();
    derviateRecursively(d_new, curNode->R, cout);

    copy = new Node(curNode->L);

    right->SET_L(d_new);
    right->SET_R(copy);
}

void Tree::make_div_derivative(Node *d_curNode, Node *curNode, std::ofstream &cout) {
    Node *left = new Node();
    d_curNode->SET_L(left);

    Data data(Data::sign_plus);
    left->setData(data);

    make_mult_deriviative(left, curNode, cout);


    Node *right = new Node(Data::sign_mult);

    d_curNode->SET_R(right);

    Node *copyL = new Node(curNode->R);
    right->SET_L(copyL);


    Node *copyR = new Node(curNode->R);
    right->SET_R(copyR);

}

void Tree::showTree(Node *curNode, std::ofstream &cout) {

    if(curNode == nullptr) {
        return;
    }

    if (curNode->L != nullptr) {
        if (curNode->DATA.TYPE == Data::sin || curNode->DATA.TYPE == Data::cos) {
            cout << curNode->DATA.toString();
        }

        if (curNode->DATA.TYPE == Data::sign_div) {
            cout << "$\\frac {";
        }

        if (isBracketNeedL(curNode)) {
            cout << "( ";
        }
        showTree(curNode->L, cout);
        if (isBracketNeedL(curNode)) {
            cout << ") ";
        }
        if (curNode->DATA.TYPE == Data::sign_div) {
            cout << "}";
        }

    }

    if (!(curNode->DATA.TYPE == Data::sin || curNode->DATA.TYPE == Data::cos || curNode->DATA.TYPE == Data::sign_div)) {
        cout << curNode->DATA.toString();
    }

    if (curNode->R != nullptr) {
        if (curNode->DATA.TYPE == Data::sign_div) {
            cout << "{";
        }
        if (isBracketNeedR(curNode)) {
            cout << "( ";
        }
        showTree(curNode->R, cout);
        if (isBracketNeedR(curNode)) {
            cout << ") ";
        }
        if (curNode->DATA.TYPE == Data::sign_div) {
            cout << "}$";
        }
    }
}

Tree::~Tree() {
    delete head;
}

bool Tree::optimize(Node *pNode) {

    if (pNode== nullptr) {
        return false;
    }
    switch (pNode->DATA.TYPE) {
        case Data::sign_plus:
        case Data::sign_mins: {
            if (pNode->L == nullptr) {
                CONST_DATA
                data.SET_NUMBER(0);
                PNODE_SET_DATA
                pNode->SET_L(nullptr);
                pNode->SET_R(nullptr);
                return false;
            }
            if (canDelete(pNode->L, 0)) {
                delete pNode->L;
                pNode->copy(pNode->R);
                return true;
            } else if (canDelete(pNode->R, 0)) {
                delete pNode->R;
                pNode->copy(pNode->L);
                return true;
            } else if (pNode->L->DATA.TYPE == Data::Type::const_number &&
                    pNode->R->DATA.TYPE == Data::Type::const_number) {
                int a = pNode->L->DATA.NUMBER;
                int b = pNode->R->DATA.NUMBER;
                int c = -1;

                delete pNode->L;
                delete pNode->R;

                switch (pNode->DATA.TYPE) {
                    case Data::sign_plus: {
                        c = (a + b);
                        break;
                    }
                    case Data::sign_mins: {
                        c = (a - b);
                        break;
                    }
                }

                pNode->SET_L(nullptr);
                pNode->SET_R(nullptr);

                CONST_DATA
                data.SET_NUMBER(c);
                PNODE_SET_DATA
                return true;
            }
            else {
                    return optimize(pNode->L) || optimize(pNode->R);
            }


        }
        case Data::sign_mult: {
            if (pNode->L == nullptr) {
                CONST_DATA
                data.SET_NUMBER(0);
                pNode->SET_L(nullptr);
                pNode->SET_R(nullptr);
                PNODE_SET_DATA
                return false;
            }
            if (canDelete(pNode->L, 1)) {
                delete pNode->L;
                pNode->copy(pNode->R);
                return true;
            } else if (canDelete(pNode->R, 1)) {
                delete pNode->R;
                pNode->copy(pNode->L);
                return true;
            } else if (pNode->L->DATA.TYPE == Data::Type::const_number &&
                       pNode->R->DATA.TYPE == Data::Type::const_number) {
                int a = pNode->L->DATA.NUMBER;
                int b = pNode->R->DATA.NUMBER;
                int c = a * b;

                delete pNode->L;
                delete pNode->R;


                pNode->SET_L(nullptr);
                pNode->SET_R(nullptr);

                CONST_DATA
                data.SET_NUMBER(c);
                PNODE_SET_DATA
                return true;
            } else {
                CONST_DATA
                data.SET_NUMBER(0);
                if (canDelete(pNode->L, 0) || canDelete(pNode->R, 0)) {
                    delete pNode->L;
                    delete pNode->R;
                    PNODE_SET_DATA
                    pNode->SET_L(nullptr);
                    pNode->SET_R(nullptr);
                    return true;
                }
                return optimize(pNode->L) || optimize(pNode->R);
            }


        }
        case Data::sign_div: {
            if (pNode->L == nullptr) {
                CONST_DATA
                data.SET_NUMBER(0);
                pNode->SET_L(nullptr);
                pNode->SET_R(nullptr);
                PNODE_SET_DATA
                return false;
            }
            if (canDelete(pNode->R, 1)) {
                delete pNode->R;
                pNode->copy(pNode->L);
                return true;
            } else if (pNode->L->DATA.TYPE == Data::Type::const_number &&
                       pNode->R->DATA.TYPE == Data::Type::const_number) {
                int a = pNode->L->DATA.NUMBER;
                int b = pNode->R->DATA.NUMBER;
                int c = a / b;

                delete pNode->L;
                delete pNode->R;


                pNode->SET_L(nullptr);
                pNode->SET_R(nullptr);

                CONST_DATA
                data.SET_NUMBER(c);
                PNODE_SET_DATA
                return true;
            }
            else {
                CONST_DATA
                data.SET_NUMBER(0);
                if (canDelete(pNode->L, 0)) {
                    delete pNode->L;
                    delete pNode->R;
                    PNODE_SET_DATA
                    pNode->SET_L(nullptr);
                    pNode->SET_R(nullptr);
                    return true;
                }
                return optimize(pNode->L) || optimize(pNode->R);
            }
        }

        case Data::sin:
        case Data::cos: {
            return optimize(pNode->L);
        }
    }

    return false;
}

bool Tree::canDelete(Node *pNode, int value) {
    if (pNode == nullptr) {
        return true;
    }
    return pNode->DATA.TYPE == Data::const_number && pNode->DATA.NUMBER == value;
}

bool Tree::isBracketNeedR(Node *curNode) {
    return (curNode->R->PRIOR < curNode->PRIOR && curNode->R->PRIOR > 0) ||
           curNode->PRIOR == 3;
}

bool Tree::isBracketNeedL(Node *curNode) {
    return (curNode->L->PRIOR < curNode->PRIOR && curNode->L->PRIOR > 0) ||
           curNode->PRIOR == 3;
}

void Tree::diriviateLatexOnly(std::string file_name) {
    std::ofstream file;
    file.open (file_name);


    Node* headDerivated = new Node;
    derviateRecursively(headDerivated, head, file);

    file << "\\documentclass[a4paper, 20pt]{article}\n"
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
            "\n";
    file << "( ";
    showTree(head, file);
    file << ")'" << " = \\\\ ";

    showTree(headDerivated, file);
    file <<"";

    while(optimize(headDerivated)) {
        int ran = rand() % 7;
        if (ran < countWord) {
            file << " \\\\ " << Tree::strings[ran]  << " \\\\ ";
        } else {
            file << " = \\\\ ";
        }
        file <<" ";
        showTree(headDerivated, file);
        file <<"  ";
    }

    file << "\n"
            "\\medskip\n"
            "\n"
            "\n"
            "\\end{document}";
    delete headDerivated;

    file.close();
}

