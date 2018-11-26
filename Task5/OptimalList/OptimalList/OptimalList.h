//
// Created by user on 03.11.18.
//

#ifndef OPTIMALLIST_OPTIMALLIST_H
#define OPTIMALLIST_OPTIMALLIST_H


#include <glob.h>
#include <ostream>
#include <fstream>
#include <iostream>
#include "../List/Node.h"

#define SIMPLE_NUMBER 11
#define MODULE 1000001

#ifdef DEBUG

#define DUMP \
         dump(std::cout); \
         std::ofstream outfile; \
         outfile.open("Log.txt"); \
         dump(outfile); \
         outfile.close(); \

#else

#define DUMP ;

#endif


#ifdef DEBUG

#define CHECK_STARTS(a)  auto codeOfIsUnchanged = isUnchanged(); \
        if (!codeOfIsUnchanged) {   \
         DUMP \
         return a; \
        }   \


#define CHECK_ENDS setCheckSum();


#else

#define CHECK_STARTS(a) ;

#define CHECK_ENDS ;


#endif

/// OPTIMAL LIST
/// All nodes in one place
template <class T>
class OptimalList {

private:

    /// Kanareika Before variables
    size_t KANAREIKA_BEGIN = 0xBEDABEDA;

    /// CurrentChecksum
    size_t checkSum = 0xBEDABEDA;



    /// Buffer where memory was allocated
    Node<T>* allocatedMemory;

    /// Pointer for unused nodes
    Node<T>* freeSpace;

    /// Pointer to the list head
    Node<T> *head;

    /// Pointer to the list tail
    Node<T> *tail;

    /// Max size of elements in list
    size_t max_size;

    /// Value to find errors
    T PoisonValue;


    /// Kanareika Before variables
    size_t KANAREIKA_END = 0xBEDABEDA;

public:
    /// Constructor Of Optimal List
    /// \param PoisonValue_ - value to catch errors
    /// \param max_size_ - size_t maximum count of elements in list
    OptimalList<T>(T PoisonValue_, size_t max_size_): head(nullptr), tail(nullptr),
            PoisonValue(PoisonValue_), max_size(max_size_) {
        allocatedMemory = new Node<T>[max_size];

        freeSpace = allocatedMemory;

        for(size_t i = 0; i < max_size; i++) {
            allocatedMemory[i].setNext(allocatedMemory + (i + 1) % max_size);
            allocatedMemory[i].setData(PoisonValue);
            allocatedMemory[i].setPrev(nullptr);
        }
        #ifdef DEBUG
        setCheckSum();
        #endif
    }

    /// Return pointer to head, maybe null
    /// \return head
    Node<T>* getFront() {
        CHECK_STARTS(nullptr)
        CHECK_ENDS
        return head;
    }

    /// Return pointer to head, maybe null
    /// \return tail
    Node<T>* getBack() {
        CHECK_STARTS(nullptr)
        CHECK_ENDS
        return tail;
    }

    /// Add element to the head
    /// If there are now empty nodes, skip adding
    /// \param elem - node to insert
    void pushFront(Node<T>& elem) {
        CHECK_STARTS(;)

        auto curEmpty = getEmpty();
        (*curEmpty) = elem;

        curEmpty->setNext(head);
        if (head == nullptr) {
            head = tail = curEmpty;
        } else {
            head->setPrev(curEmpty);
        }
        head = curEmpty;

        CHECK_ENDS
    }

    /// Add element to the tail
    /// If there are now empty nodes, skip adding
    /// \param elem - node to insert
    void pushBack(Node<T>& elem) {
        CHECK_STARTS(;)

        auto curEmpty = getEmpty();
        (*curEmpty) = elem;

        curEmpty->prev = tail;
        if (tail == nullptr) {
            head = tail = curEmpty;
        } else {
            tail->next = curEmpty;
        }
        tail = curEmpty;

        CHECK_ENDS
    }

    /// Delete first element if exist
    void popFront() {
        CHECK_STARTS(;)

        if (head == nullptr) {
            CHECK_ENDS
            return;
        }
        head->setData(PoisonValue);

        if (freeSpace == nullptr) {
            freeSpace = head;
        } else {
            head->next = freeSpace;
            freeSpace->prev = head;
            freeSpace = head;
        }

        if (head != tail) {
            head = head->next;
            head->prev = nullptr;
        } else {
            tail = head = nullptr;
        }

        CHECK_ENDS
    }

    /// Delete last element if exist
    void popBack() {
        CHECK_STARTS(;)
        if (tail == nullptr) {
            CHECK_ENDS
            return;
        }

        tail->data = PoisonValue;

        if (freeSpace == nullptr) {
            freeSpace = tail;
        } else {
            tail->next = freeSpace;
            freeSpace->prev = tail;
            freeSpace = tail;
        }

        if (head != tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            tail = head = nullptr;
        }

        CHECK_ENDS
    }

    /// Add element after pos
    /// If there are now empty nodes, skip adding
    /// \param pos - position after what we must insert
    /// \param elem - node to insert
    void insert(Node<T>* pos, Node<T>& elem) {
        CHECK_STARTS(;)

        Node<T>* empty = getEmpty();
        if (empty == nullptr) {
            CHECK_ENDS
            return; // SKIIIPP!!! LOL, Stupid user))
        }
        (*empty) = elem;

        if (pos->next != nullptr) {
            pos->getNext()->setPrev(empty);
            empty->setNext(pos->getNext());
        } else {
            tail = empty;
        }
        empty->prev = pos;
        pos->next = empty;

        CHECK_ENDS
    }

    /// Return next element after element
    /// \param elem - node to get next position
    /// \return pointer to next element
    Node<T>* getNext(Node<T>* elem) {
        CHECK_STARTS(nullptr)

        CHECK_ENDS
        return elem->getNext();
    }

    /// Return prev element after element
    /// \param elem - node to get prev position
    /// \return pointer to prev element
    Node<T>* getPrev(Node<T>* elem) {
        CHECK_STARTS(nullptr)
        CHECK_ENDS

        return elem->getPrev();
    }

    /// Deleting allocated Memory
    ~OptimalList() {
        delete[] allocatedMemory;
    }

private:
    Node<T>* getEmpty() {
        CHECK_STARTS(nullptr)
        if (freeSpace == nullptr) {
            CHECK_ENDS
            return nullptr;
        }
        Node<T>* temp = freeSpace;
        freeSpace = freeSpace->next;

        CHECK_ENDS
        return temp;
    }

#ifdef DEBUG
    /// Show all relevant information of object, IF DEBUG MODE
    /// \param out - stream to write
    void dump(std::ostream& out) const {

        out << "class OptimalList {" << std::endl;
        out << "    /// Kanareika Before variables" << std::endl;
        out << "    size_t KANAREIKA_BEGIN = " << KANAREIKA_BEGIN << " --- MUST BE " << 0xBEDABEDA << std::endl;
        out << "    size_t checkSum = 0xBEDABEDA;\n";
        out << "    Node<T>* allocatedMemory = " << allocatedMemory << std::endl;

        for(size_t i = 0; i < max_size; i++) {
            out << "        allocatedMemory[" << i << "] = " << &allocatedMemory[i] << std::endl;
        }

        out << "    Node<T>* freeSpace = " << freeSpace << std::endl;
        out << "    Node<T> *head = " << head << std::endl;
        out << "    Node<T> *tail = " << tail << std::endl;
        out << "    size_t max_size = " << max_size << std::endl;
        out << "    T PoisonValue = " << PoisonValue << std::endl;
        out << "    /// CurrentChecksum" << std::endl;
        out << "    size_t checkSum = " << checkSum << std::endl;
        out << "    /// Kaanreika after variables" << std::endl;
        out << "   size_t KANAREIKA_END = " << KANAREIKA_END << " --- MUST BE " << 0xBEDABEDA << std::endl;
        out << "}" << std::endl;

    }

    /// checksum calculation
    /// \return current checksum
    size_t getCheckSum() const {
        size_t cacheSum  = 5;
        std::hash<Node<T> *> hashFunc;
        for (size_t i = 0; i < max_size; i++) {
            cacheSum = ((cacheSum * SIMPLE_NUMBER) + hashFunc(&allocatedMemory[i])) % MODULE;
        }
        return cacheSum;
    }

    bool isUnchanged() const {
        auto codeOfIsValide = isValid();
        if (!codeOfIsValide) {
            return codeOfIsValide;
        }

        size_t currentCheckSum = getCheckSum();

        return currentCheckSum == checkSum;

        // everything is OK
    }


    /// Calculate and set new checksum
    void setCheckSum() {
        checkSum = getCheckSum();
    }
    /// Check if kanareika is not changed, array not changed, etc.
    /// \return ErrorCode
    bool isValid() const {
        if (max_size < 0) {
            return false; // error in size of count
        }
        return !(KANAREIKA_BEGIN != KANAREIKA_END || KANAREIKA_BEGIN != 0xBEDABEDA); // everything is OK
    }

#endif


};


#endif //OPTIMALLIST_OPTIMALLIST_H
