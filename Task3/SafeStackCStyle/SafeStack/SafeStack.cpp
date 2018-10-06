//
// Created by user on 02.10.18.
//

#include <functional>
#include "SafeStack.h"

#define CHECK_BEFORE(block) \
        auto codeOfIsUnchanged = isUnchanged(); \
        if (codeOfIsUnchanged != 0) {   \
         return codeOfIsUnchanged; \
        }   \
        block  \
        setCheckSum();  \

#define CHECK_BEFORE_PAIR(block) \
        auto codeOfIsUnchanged = isUnchanged(); \
        if (codeOfIsUnchanged != 0) {   \
         return std::make_pair(POISON, codeOfIsUnchanged); \
        }   \
        block  \
        setCheckSum();  \

template<typename Type>
size_t SafeStack<Type>::getCheckSum() const {
    size_t cacheSum  = 5;
    std::hash<Type> hashFunc;
    for (size_t i = 0; i < count; i++) {
        cacheSum = ((cacheSum * SIMPLE_NUMBER) + hashFunc(container[i])) % MODULE;
    }
    return cacheSum;
}

template<typename Type>
void SafeStack<Type>::setCheckSum() {
    checkSum = getCheckSum();
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::isValid() const {
    if (count < 0 || count >= MAX_SIZE) {
        return ErrorCountSize; // error in size of count
    }
    if (KANAREIKA_STARTING != KANAREIKA_ENDING || KANAREIKA_ENDING != 0xBEDABEDA) {
        return ErroKanareika; // Error with Kanareika
    }
    for (size_t i = count; i < MAX_SIZE; i++) {
        if (container[i] != POISON) {
            return ErrorPoison; // POISON VALUE NOT IN ARRAY
        }
    }
    return OK; // everything is OK
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::isUnchanged() const {
    auto codeOfIsValide = isValid();
    if (codeOfIsValide != 0) {
        return codeOfIsValide;
    }

    size_t currentCheckSum = getCheckSum();
    if (currentCheckSum != checkSum) {
        return ErrorCheckSum; // checkSum != currentCheckSum
    }

    return OK; // everything is OK
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::pop() {
    if (count == 0) {
        return ErrorPop; // Nothing to POP
    }
    CHECK_BEFORE({count--; container[count] = POISON;});
    return OK;
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::push(Type element) {
    if (count == MAX_SIZE) {
        return ErrorPush; // Container is full
    }
    CHECK_BEFORE(container[count] = element; count++;);
    return OK;
}

template<typename Type>
Type SafeStack<Type>::getFrontUnsafe() {
    if (count >= 1) {
        return container[count - 1];
    }
    // ERROR!!!!
}

template<typename Type>
std::pair<Type, typename SafeStack<Type>::ErrorCodes> SafeStack<Type>::getFrontSafe() {
    if (count == 0) {
        return std::make_pair(POISON, ErrorPop); // Nothing to show
    }
    CHECK_BEFORE_PAIR()

    return std::make_pair(getFrontUnsafe(), OK);
}

template<typename Type>
SafeStack<Type>::SafeStack(Type poison_) {
    POISON = poison_;
    for (size_t i = 0; i < MAX_SIZE; i++) {
        container[i] = POISON;
    }
    setCheckSum();
}
