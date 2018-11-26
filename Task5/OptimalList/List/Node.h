//
// Created by user on 03.11.18.
//

#ifndef OPTIMALLIST_LIST_H
#define OPTIMALLIST_LIST_H


template <class T>
class Node {
public:
    Node* next, *prev;
    T data;

public:
    Node<T> (): next(nullptr), prev(nullptr) {}

    Node<T>(Node<T>& obj_): next(nullptr), prev(nullptr) {
        this->data = obj_.data;
    }

    Node(Node *next, Node *prev, T data) : next(next), prev(prev), data(data) {}

    Node *getNext() const {
        return next;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

    Node *getPrev() const {
        return prev;
    }

    void setPrev(Node *prev) {
        Node::prev = prev;
    }

    T getData() const {
        return data;
    }

    void setData(T data) {
        Node::data = data;
    }

};


#endif //OPTIMALLIST_LIST_H
