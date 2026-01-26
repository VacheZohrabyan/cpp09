#include "RPN.hpp"

int main(int argc, char** argv)
{
    try
    {
        if (argc != 2)
            throw (Rpn::Error("too many or less argument"));
        Rpn(std::string(argv[1]));
    }
    catch(const Rpn::Error& e)
    {
        std::cout << e.what() << "\n";
    }
}