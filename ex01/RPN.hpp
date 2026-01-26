#pragma once

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <vector>
#include <cstdlib>

class Rpn
{
public:
    Rpn(const std::string& argv);
    ~Rpn();
    Rpn();
    Rpn(const Rpn& other);
    Rpn& operator=(const Rpn& other);

private:
    void calculate(const std::string& input);

private:
    std::stack<double> _storage;

public:
    class Error : public std::exception
    {
    private:
        std::string message;
    public:
        Error(const std::string message) : message(message) {}
        ~Error() throw() {}
    public:
        const char* what() const throw();
    };
};

// std::ostream& operator<<(std::ostream& os, Rpn::Error& e)
// {
//     os << e.what() << "\n";
//     return os;
// }

#endif