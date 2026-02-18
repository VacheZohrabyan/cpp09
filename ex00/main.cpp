#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    (void)argv;
    if (argc != 2)
        return (ErrorMessage("could not open file."), 0);
    try
    {
        BitcoinExchange btc("data.csv");
        btc.parseInpute(argv[argc - 1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}