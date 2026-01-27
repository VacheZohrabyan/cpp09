#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int ac, char **av){

    std::deque<int> inputDeque;
    std::list<int> inputList;
    srand(time(NULL));
    for (int i = 1; i < ac; ++i)
    {
        int value = atoi(av[i]);
        if (value <= 0)
        {
            std::cerr << "Error: Invalid input value \"" << av[i] << "\". Only positive integers are allowed." << std::endl;
			exit(1);
        }
        inputDeque.push_back(value);
        inputList.push_back(value);
    }
    std::cout << "Before: ";
    display(inputDeque);
    clock_t start1 = clock();
    mergeInsertSortDeque(inputDeque);
    clock_t end1 = clock();
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;
    clock_t start2 = clock();
    mergeInsertSortList(inputList);
    clock_t end2 = clock();
    double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000;
    std::cout << "After: ";
    display(inputDeque);
    std::cout << "Time to process a range of " << inputDeque.size() << " elements with std::deque container: " << time1 << " us" << std::endl;
    std::cout << "Time to process a range of " << inputList.size() << " elements with std::list container: " << time2 << " us" << std::endl;
    if (inputDeque == std::deque<int>(inputList.begin(), inputList.end()))
        std::cout << "The sorted sequences are equal." << std::endl;
    else
        std::cout << "The sorted sequences are not equal." << std::endl;
}

template <typename T>
void PmergeMe::display(const T& container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;
    std::deque<int> big;
    std::deque<int> small;
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] < arr[i+1])
        {
            small.push_back(arr[i]);
            big.push_back(arr[i+1]);
        }
        else
        {
            small.push_back(arr[i+1]);
            big.push_back(arr[i]);
        }
    }
    if (arr.size() % 2)
        small.push_back(arr.back());
    mergeInsertSortDeque(big);
    arr = big;
    for (size_t i = 0; i < small.size(); ++i)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(arr.begin(), arr.end(), small[i]);
        arr.insert(pos, small[i]);
    }
}

void PmergeMe::mergeInsertSortList(std::list<int>& arr)
{
    if (arr.size() <= 1)
        return;
    std::list<int> big, small;
    std::list<int>::iterator it = arr.begin();
    while (it != arr.end())
    {
        int a = *it++;
        if (it == arr.end())
        {
            small.push_back(a);
            break;
        }
        int b = *it++;
        if (a < b)
        {
            small.push_back(a);
            big.push_back(b);
        }
        else
        {
            small.push_back(b);
            big.push_back(a);
        }
    }
    mergeInsertSortList(big);
    arr = big;
    for (std::list<int>::iterator s = small.begin(); s != small.end(); ++s)
    {
        std::list<int>::iterator pos = arr.begin();
        while (pos != arr.end() && *pos < *s)
            ++pos;
        arr.insert(pos, *s);
    }
}