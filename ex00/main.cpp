#include "BitcoinExchange.hpp"

void ErrorMessage(std::string message)
{
    std::cout << "Error: " << message << std::endl;    
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return (ErrorMessage("could not open file."), 0);
    BitcoinExchange(argv[argc - 1]);
}