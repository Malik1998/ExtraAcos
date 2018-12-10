//
// Created by user on 26.11.18.
//

#include "Node.h"

Node *Node::getLeft() const {
    return left;
}

void Node::setLeft(Node *left) {
    Node::left = left;
}

Node *Node::getRight() const {
    return right;
}

void Node::setRight(Node *right) {
    Node::right = right;
}


const Data &Node::getData() const {
    return data;
}

void Node::setData(const Data &data) {
    Node::data = data;
}

Node::Node() {}

Node::Node(Node *pNode) {
    if (pNode == nullptr) {
        return ;
    }
    this->data = pNode->data;
    if (pNode->getLeft() != nullptr) {
        Node *left_ = new Node(pNode->getLeft());

        this->left = left_;
    }

    if (pNode->getRight() != nullptr) {
        Node *right_ = new Node(pNode->getRight());

        this->right = right_;
    }
}

Node::Node(Data::Type type) {
    this->data = Data(type);
}

void Node::copy(Node *pNode) {
    this->data = pNode->getData();
    this->left = pNode->getLeft();
    this->right = pNode->getRight();
}

int Node::getPriority() {
    switch (data.getType()) {
        case(Data::sign_plus):
        case(Data::sign_mins):
            return 1;
        case(Data::sign_mult):
        case(Data::sign_div):
            return 2;
        case(Data::sin):
        case(Data::cos):
            return 3;
        case(Data::const_number):
        case(Data::variable):
            return -1;
    }
}
