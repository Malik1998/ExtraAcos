//
// Created by user on 09.09.18.
//

#ifndef QUADRICQUATIONS_RESULT_H
#define QUADRICQUATIONS_RESULT_H


#include <cstdio>
#include <set>

/// Class to use results of solving quatations. Singletone
class Result {

public:
    /// Type of count of roots
    /// Countable - numeric count
    /// Infinity_count - infinity number roots
    /// None - no roots
    enum TYPE_OF_ROOTS {COUNTABLE, INFINITY_COUNT, NONE};

public:
    ///  Result object with typeOfRoots set to INFINITY_COUNT
    /// Other variables don't used.
    /// static varible will be not created again
    /// \return this created Result object
    static Result getInfinityRoots();
    /// Result object with typeOfRoots set to NONE
    /// Other variables don't used.
    /// static varible will be not created again
    /// \return this created Result object
    static Result getNoneRoots();
    /// roots will be moved from parameter, count_of_roots set to roots.size()
    /// and type_of_roots set to Countable
    /// \param roots - set of all roots of quatation, will be moved
    /// \return This Result object
    static Result getCountableRoots(std::set<double>&& roots);
    /// roots will be copied from parameter, count_of_roots set to roots.size()
    /// and type_of_roots set to Countable
    /// \param roots - set of all roots of quatation, will be copied
    /// \return This Result object
    static Result getCountableRoots(std::set<double>& roots);

    /// acces to private member
    /// \return typeOfRoots
    TYPE_OF_ROOTS getTypeOfRoots();
    /// acces to private member
    /// copy of roots set is returned, if type is countable,
    /// otherwise assert thrown
    /// \return copy of roots set, if type is countable
    std::set<double> getRoots();

    /// access to private member
    /// count of roots set is returned, if type is countable,
    /// otherwise assert thrown
    /// \return count of roots set, if type is countable
    size_t getCount();



private:
    /// Singletone, constructor never used!!!
    Result() = default;

private:
    /// adequate count if typeOfRoots is countable,
    /// otherwise 0
    size_t count_of_roots = 0;
    /// type of result
    TYPE_OF_ROOTS typeOfRoots;
    /// set of roots if type of roots is countable
    std::set<double> roots;
    /// Object with infinity roots
    static Result INFINITY_ROOTS;
    /// Object with none roots
    static Result NONE_ROOTS;
};

#endif //QUADRICQUATIONS_RESULT_H
