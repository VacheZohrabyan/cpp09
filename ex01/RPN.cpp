#include "RPN.hpp"

Rpn::Rpn(const std::string &argv)
{
    calculate(argv);
}

Rpn::~Rpn()
{

}

Rpn::Rpn()
{

}

Rpn::Rpn(const Rpn& other)
{
    *this = other;
}

Rpn& Rpn::operator=(const Rpn& other)
{
    if (this != &other)
        *this = other;
    return *this;
}

void Rpn::calculate(const std::string& input)
{
    for (std::string::size_type i = 0; i < input.size(); ++i)
    {
        if (input[i] == ' ')
            continue;
        else if (isdigit(input[i]))
            _storage.push(input[i] - '0');
        else if (input[i] == '+' && _storage.size() >= 2)
        {
            double a = _storage.top();
            _storage.pop();
            double b = _storage.top();
            _storage.pop();
            _storage.push(b + a);
        }
        else if (input[i] == '-' && _storage.size() >= 2)
        {
            double a = _storage.top();
            _storage.pop();
            double b = _storage.top();
            _storage.pop();
            _storage.push(b - a);
        }
        else if (input[i] == '*' && _storage.size() >= 2)
        {
            double a = _storage.top();
            _storage.pop();
            double b = _storage.top();
            _storage.pop();
            _storage.push(b * a);
        }
        else if (input[i] == '/' && _storage.size() >= 2)
        {
            double a = _storage.top();
            _storage.pop();
            double b = _storage.top();
            _storage.pop();
            _storage.push(b / a);
        }
        else
        {
            std::cout << "Error\n";
            return;
        }
    }

    if (_storage.size() != 0)
        std::cout << _storage.top();
    else
        std::cout << "Error\n";
}

const char* Rpn::Error::what() const throw()
{
    return message.c_str();
}