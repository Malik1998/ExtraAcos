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

Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *parent) {
    Node::parent = parent;
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
        left_->parent = this;

        this->left = left_;
    }

    if (pNode->getRight() != nullptr) {
        Node *right_ = new Node(pNode->getRight());
        right_->parent = this;

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
