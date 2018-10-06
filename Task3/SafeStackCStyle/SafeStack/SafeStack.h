//
// Created by user on 02.10.18.
//

#ifndef SAFESTACKCSTYLE_SAFESTACK_H
#define SAFESTACKCSTYLE_SAFESTACK_H


#include <cstdio>
#include <utility>

#define MAX_SIZE 100
#define SIMPLE_NUMBER 11
#define MODULE 1000001

/// SafeStack not look for own memory carefully
/// \tparam Type - type of elements in stack must have hash() function
template <typename Type> class SafeStack {
    /// Kanareika Before variables
    size_t KANAREIKA_STARTING = 0xBEDABEDA;
    /// Stack - container
    Type container[MAX_SIZE];
    /// Real count of elemnts now in stack
    size_t count = 0;
    /// Poisn value that can be used in stack
    Type POISON;

    /// CurrentChecksum
    size_t checkSum = 0xBEDABEDA;

public:
    enum ErrorCodes {
        OK, //!< Everything is OK // 0
        ErrorCountSize, //!< Size of Count is too big or small // 1
        ErrorPoison, //!< Posion value not in array // 2
        ErrorCheckSum, //!< Current Checksum is unequal with saved Checksum // 3
        ErrorPop, //!< Nothin to Pop // 4
        ErrorPush, //!< Container is full // 5
        ErroKanareika //!< Kanareika is not equal to 0xBEDABEDA // 6
    };

    /// Kaanreika after variables
    size_t KANAREIKA_ENDING = 0xBEDABEDA;


public:
    /// Fill container with poison_ value, count checksum
    /// \param poison_ - element that will not be in stack
    SafeStack(Type poison_);
    /// Check if checksum not changed
    /// \return ErrorCode
    ErrorCodes isUnchanged() const;
    /// Remove Last element
    /// If it has no last element error returned
    /// \return ErrorCode
    ErrorCodes pop();
    /// Add element to front
    /// If stack is full returns Error
    /// \param element - element to push
    /// \return ErrorCode
    ErrorCodes push(Type element);
    /// CAUTION!!! - Not use it if you are not sure!!!
    /// \return front element  without checking
    Type getFrontUnsafe();
    ///
    /// \return pair where first element - is Front element if exists, else Poison value. second - ErrorCode
    std::pair<Type, ErrorCodes> getFrontSafe();

private:
    /// checksum calculation
    /// \return current checksum
    size_t getCheckSum() const;
    /// Calculate and set new checksum
    void setCheckSum();
    /// Check if kanareika is not changed, array not changed, etc.
    /// \return ErrorCode
    ErrorCodes isValid() const;

};


#endif //SAFESTACKCSTYLE_SAFESTACK_H
