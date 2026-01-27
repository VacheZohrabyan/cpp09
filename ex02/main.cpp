#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Error\n";
        return 0;
    }
    PmergeMe(argc, argv);
}