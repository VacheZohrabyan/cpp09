#pragma once
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <ctime>
#include <cstdlib>

class PmergeMe
{
public:
    PmergeMe(int argc, char** argv);

public:
    template<typename T>
    void display(const T& input);
    void mergeInsertSortDeque(std::deque<int>& inputDeque);
    void mergeInsertSortList(std::list<int>& arr);
};

#endif