//
// Created by user on 09.09.18.
//

#include <assert.h>
#include <iostream>
#include "Result.h"

Result Result::INFINITY_ROOTS = Result();
Result Result::NONE_ROOTS = Result();


Result Result::getInfinityRoots() {
    INFINITY_ROOTS.typeOfRoots = INFINITY_COUNT;
    return INFINITY_ROOTS;
}

Result Result::getNoneRoots() {
    NONE_ROOTS.typeOfRoots = NONE;
    return NONE_ROOTS;
}

Result Result::getCountableRoots(std::set<double>&& roots) {
    Result countableRoots = Result();
    countableRoots.typeOfRoots = COUNTABLE;
    countableRoots.roots = std::move(roots);
    countableRoots.count_of_roots = countableRoots.roots.size();
    return countableRoots;
}

Result Result::getCountableRoots(std::set<double>& roots) {
    Result Countable_ROOTS = Result();
    Countable_ROOTS.typeOfRoots = COUNTABLE;
    Countable_ROOTS.roots = roots;
    Countable_ROOTS.count_of_roots = roots.size();
    return Countable_ROOTS;
}

Result::TYPE_OF_ROOTS Result::getTypeOfRoots() {
    return typeOfRoots;
}

std::set<double> Result::getRoots() {
    assert(typeOfRoots == COUNTABLE || typeOfRoots == NONE);
    return roots;
}

size_t Result::getCount() {
    assert(typeOfRoots != INFINITY_COUNT);
    return count_of_roots;
}
