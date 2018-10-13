//
// Created by user on 02.10.18.
//
#ifndef SAFESTACKCSTYLE_SAFESTACK_CPP
#define SAFESTACKCSTYLE_SAFESTACK_CPP
#include <functional>
#include <ostream>
#include "SafeStack.h"
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <algorithm>

#ifdef DEBUG
#define DUMP \
         dump(std::cout); \

#else
#define DUMP
#endif

#define CHECK_BEFORE_AND_SET_CHECKSUM(block) \
        auto codeOfIsUnchanged = isUnchanged(); \
        if (codeOfIsUnchanged != 0) {   \
         DUMP \
         return codeOfIsUnchanged; \
        }   \
        block  \
        setCheckSum();  \

#define CHECK_BEFORE_PAIR_AND_SET_CHECKSUM(block) \
        auto codeOfIsUnchanged = isUnchanged(); \
        if (codeOfIsUnchanged != 0) {   \
         DUMP \
         return std::make_pair(POISON_, codeOfIsUnchanged); \
        }   \
        block  \
        setCheckSum();  \

template<typename Type>
size_t SafeStack<Type>::getCheckSum() const {
    size_t cacheSum  = 5;
    std::hash<Type> hashFunc;
    for (size_t i = 0; i < count_; i++) {
        cacheSum = ((cacheSum * SIMPLE_NUMBER_) + hashFunc(container_[i])) % MODULE_;
    }
    return cacheSum;
}

template<typename Type>
void SafeStack<Type>::setCheckSum() {
    checkSum_ = getCheckSum();
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::isValid() const {
    if (count_ < 0 || count_ >= MAX_SIZE_) {
        return ErrorCountSize; // error in size of count_
    }
    if (KANAREIKA_STARTING_ != KANAREIKA_ENDING_ || KANAREIKA_ENDING_ != 0xBEDABEDA) {
        return ErroKanareika; // Error with Kanareika
    }
    for (size_t i = count_; i < MAX_SIZE_; i++) {
        if (container_[i] != POISON_) {
            return ErrorPoison; // POISON_ VALUE NOT IN ARRAY
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
    if (currentCheckSum != checkSum_) {
        return ErrorCheckSum; // checkSum_ != currentCheckSum
    }

    return OK; // everything is OK
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::pop() {
    if (count_ == 0) {
        DUMP
        return ErrorPop; // Nothing to POP
    }
    CHECK_BEFORE_AND_SET_CHECKSUM({count_--; container_[count_] = POISON_;});
    return OK;
}

template<typename Type>
typename SafeStack<Type>::ErrorCodes SafeStack<Type>::push(Type element) {
    if (count_ == MAX_SIZE_) {
        DUMP
        return ErrorPush; // Container is full
    }
    CHECK_BEFORE_AND_SET_CHECKSUM(container_[count_] = element; count_++;);
    return OK;
}

template<typename Type>
Type SafeStack<Type>::getFrontUnsafe() const{
    if (count_ >= 1) {
        return container_[count_ - 1];
    }
    // ERROR!!!!
}

template<typename Type>
std::pair<Type, typename SafeStack<Type>::ErrorCodes> SafeStack<Type>::getFrontSafe() {
    if (count_ == 0) {
        return std::make_pair(POISON_, ErrorPop); // Nothing to show
    }
    CHECK_BEFORE_PAIR_AND_SET_CHECKSUM()

    return std::make_pair(getFrontUnsafe(), OK);
}

template<typename Type>
SafeStack<Type>::SafeStack(Type poison_) : POISON_(poison_) {
    std::fill(container_, container_ + MAX_SIZE_, POISON_);
    setCheckSum();
}

#ifdef DEBUG
template<typename Type>
void SafeStack<Type>::dump(std::ostream &out) const {

    out << "class SafeStack {" << std::endl;
    out << "    /// Kanareika Before variables" << std::endl;
    out << "    size_t KANAREIKA_STARTING_ = " << KANAREIKA_STARTING_ << " --- MUST BE " << 0xBEDABEDA << std::endl;
    out << "    /// Stack - container_" << std::endl;
    out << "    "<< typeid(Type).name()  << " container_[MAX_SIZE_] { " << std::endl;

    for(size_t i = 0; i < MAX_SIZE_; i++) {
        out << "    container_[" << i << "] = " << container_[i];
        if (i >= count_) {
            out << " * <---- MUST BE POISON_, " << "We SUPPOSE THAT POISON_ = " << POISON_;
        }
        out << std::endl;
    }


    out << "     }" << std::endl;
    out << "    /// Real count_ of elemnts now in stack" << std::endl;
    out << "    size_t count_ = " << count_ << std::endl;
    out << "    /// Poisn value that can be used in stack" << std::endl;
    out << "    " << typeid(Type).name() << " POISON_ = " << POISON_ << std::endl;
    out << "    /// CurrentChecksum" << std::endl;
    out << "    size_t checkSum_ = " << checkSum_ << std::endl;
    out << "    /// Kaanreika after variables" << std::endl;
    out << "   size_t KANAREIKA_ENDING_ = " << KANAREIKA_ENDING_ << " --- MUST BE " << 0xBEDABEDA << std::endl;
    out << "}" << std::endl;

}
#endif

#endif //SAFESTACKCSTYLE_SAFESTACK_CPP