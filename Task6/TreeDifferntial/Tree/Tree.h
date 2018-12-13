//
// Created by user on 26.11.18.
//

#ifndef TREEDIFFERNTIAL_TREE_H
#define TREEDIFFERNTIAL_TREE_H


#include <string>
#include "../Node/Node.h"

class Tree {

    Node *head;
    std::string expression;

    static const int countWord = 3;
    const char* strings[countWord] = {"Trivially equal to ", "Obviously equal to ", "Clear equal to "};

    enum TypeParse {
        sign,
        function,
        const_number,
        variable,
        open_bracket,
        close_bracket
    } type;

public:
    Tree(std::string expression_);
    void diriviate(std::string file_name = "derrivative");
    void diriviateLatexOnly(std::string file_name = "derrivative");
    ~Tree();

private:
    void generateTree();

    TypeParse getTypeParse(char &i);

    void recursivelyBuild(size_t &i, Node *pNode);

    int getNumber(size_t &i);

    Data::Type getSign(size_t &i);

    Data::Type getFuncName(size_t &i);

    void derviateRecursively(Node *pNode, Node *curNode, std::ofstream &cout);

    void make_mult_deriviative(Node *d_curNode, Node *curNode, std::ofstream &cout);

    void make_div_derivative(Node *d_curNode, Node *curNode, std::ofstream &cout);

    void showTree(Node *curNode, std::ofstream &cout);

    bool optimize(Node *pNode);

    bool canDelete(Node *pNode, int value);

    bool isBracketNeedR(Node *curNode);
    bool isBracketNeedL(Node *curNode);
};


#endif //TREEDIFFERNTIAL_TREE_H
