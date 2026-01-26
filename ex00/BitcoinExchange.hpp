#pragma once
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <iomanip>

class BitcoinExchange
{
public:
    BitcoinExchange(const std::string& filename);
    ~BitcoinExchange();

private:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator= (const BitcoinExchange& other);

public:
    void loadDatabase(const std::string& filename);
    void parseInpute(const std::string& filename) const;

private:
    bool is_valid_exchange_rate(const std::string& text, std::size_t pos) const;
    bool is_valid_date(const std::string& text, std::size_t pos) const;
    void insert_storage(const std::string& text);
    void parse_value(const std::string& text) const;
    void find_date_and_print(const std::string& text, std::size_t pos) const;
private:
    std::map<std::string, float> storage_db;

public:
    class File_is_not_open : public std::exception
    {
    public:
        const char* what() const throw();
    };

    class Invalid_data_storage : public std::exception
    {
    public:
        const char* what() const throw();
    };

    class Invalid_date : std::exception
    {
    public:
        const char* what() const throw();
    };

    class Invalid_exchange_rate : std::exception
    {
    public:
        const char* what() const throw();
    };
};

void ErrorMessage(std::string message);

#endif