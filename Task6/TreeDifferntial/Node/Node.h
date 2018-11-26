//
// Created by user on 26.11.18.
//

#ifndef TREEDIFFERNTIAL_NODE_H
#define TREEDIFFERNTIAL_NODE_H


#include "../Data/Data.h"

class Node {
public:
    Node();

    Node(Node *pNode);

    Node(Data::Type type);

    Node *getLeft() const;

    void setLeft(Node *left);

    Node *getRight() const;

    void setRight(Node *right);

    Node *getParent() const;

    void setParent(Node *parent);

    const Data &getData() const;

    void setData(const Data &data);

    void copy(Node *pNode);

private:

    Node *left = nullptr, *right = nullptr;
    Node *parent = nullptr;
    Data data;

};


#endif //TREEDIFFERNTIAL_NODE_H
