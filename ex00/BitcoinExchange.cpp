#include "BitcoinExchange.hpp"

void ErrorMessage(std::string message)
{
    std::cout << "Error: " << message << std::endl;    
}

BitcoinExchange::BitcoinExchange(const std::string& filename)
{
    loadDatabase(filename);
}

BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream open_db(filename.c_str());
    try
    {
        if (!open_db.is_open())
            throw File_is_not_open();
        std::string text;
        while (std::getline(open_db, text))
        {
            if (text.empty())
                return open_db.close();
            if (text == "date,exchange_rate")
                continue;
            insert_storage(text);
        }
        open_db.close();
    }
    catch(const File_is_not_open& e)
    {
        std::cout << e.what() << "\n";
    }
    catch(const Invalid_data_storage& e)
    {
        std::cout << e.what() << "\n";
    }
    catch(const Invalid_date &e)
    {
        std::cout << e.what() << "\n";
    }
    catch (const Invalid_exchange_rate& e)
    {
        std::cout << e.what() << "\n";
    }
    // for (std::map<std::string, float>::const_iterator it = storage_db.begin(); it != storage_db.end(); ++it)
    //     std::cout << "key = " << it->first << " value = " << std::fixed << std::setprecision(2) << it->second << std::endl;
}

void BitcoinExchange::parseInpute(const std::string& filename) const
{
    std::ifstream open_input(filename.c_str());
    if (!open_input.is_open())
        throw File_is_not_open();
    std::string text;
    std::getline(open_input, text);
    if (text != "date | value")
        return (void)(std::cout << "Bad format, " << text << std::endl), open_input.close();
    while (std::getline(open_input, text))
    {
        if (text == "date | value")
            continue;
        if (text.empty())
            return open_input.close();
        parse_value(text);
    }
    open_input.close();
}

void BitcoinExchange::parse_value(const std::string& text) const
{
    std::size_t pos = text.find('|');
    if (pos == std::string::npos || pos == text.size() - 1)
        return ErrorMessage("bad input => " + text);
    find_date_and_print(text, pos);
}

void BitcoinExchange::find_date_and_print(const std::string& text, std::size_t pos) const
{
    std::map<std::string, float>::const_iterator it = storage_db.lower_bound(text.substr(0, pos));
    
    if (it == storage_db.end() || it->first > text.substr(0, pos))
    {
        if (it == storage_db.begin())
            return ErrorMessage("bad input => " + it->first);
        --it;
    }
    double result = std::atof(text.substr(pos + 1).c_str());
    if (result >= 1000)
        return ErrorMessage("too large a number.");
    if (result <= 0)
        return ErrorMessage("not a positive number.");
    result *= it->second;
    std::cout << text.substr(0, pos) << "=>" << text.substr(pos + 1) << " = " << result << std::endl;
}

void BitcoinExchange::insert_storage(const std::string& text)
{
    std::size_t pos = text.find(',');
    try
    {
        if (pos == std::string::npos)
            throw Invalid_data_storage();
        if (!is_valid_date(text, pos))
            throw Invalid_date();
        if (!is_valid_exchange_rate(text, pos + 1))
            throw Invalid_exchange_rate();
        double tmp = 0.00f;
        tmp = std::atof(text.substr(pos + 1).c_str());
        storage_db.insert(std::make_pair(text.substr(0, pos), tmp));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool BitcoinExchange::is_valid_date(const std::string& text, std::size_t pos) const
{
    if (pos != 10)
        return false;
    if (text[4] != '-' && text[7] != '-')
        return false;
    for (std::size_t i = 0; i < text.size() - pos; ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(text[i]))
            return false;
    }
    int year = std::atoi(text.substr(0, 4).c_str());
    int mounth = std::atoi(text.substr(5, 7).c_str());
    int day = std::atoi(text.substr(8, pos).c_str());
    if (mounth < 1 || mounth > 12)
        return false;
    int daysMounth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mounth == 2)
    {
        bool tmp = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
        if (tmp)
            daysMounth[1] = 29; 
    }
    if (day < 1 || day > daysMounth[mounth - 1])
    {
        std::cout << mounth << std::endl;
        std::cout << daysMounth[mounth - 1];
        return false;
    }
    return true;
}

bool BitcoinExchange::is_valid_exchange_rate(const std::string& text, std::size_t pos) const
{
    if (pos < 11)
        return false;
    bool point = false;
    for (std::size_t i = pos; i < text.size(); ++i)
    {
        if (text[i] == '.')
        {
            if (point)
                throw Invalid_exchange_rate();
            point = true;
            continue;
        }
        if (!isdigit(text[i]))
            return false;
    }
    if (std::atof(text.substr(pos, text.size()).c_str()) < 0)
        return false;
    return true;
}

const char* BitcoinExchange::File_is_not_open::what() const throw()
{
    return "file_is_not_open";
}

const char* BitcoinExchange::Invalid_data_storage::what() const throw()
{
    return "invalid_data_storage";
}

const char* BitcoinExchange::Invalid_date::what() const throw()
{
    return "invalid_date";
}

const char* BitcoinExchange::Invalid_exchange_rate::what() const throw()
{
    return "invalid_exchange_rate";
}