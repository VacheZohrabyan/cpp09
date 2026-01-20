#include "BitcoinExchange.hpp"

static void openFile(std::ifstream& file, const char* argv)
{
    file.open(argv);
    if (!file.is_open())
        throw std::runtime_error("file not found");
}

static void add_storage(std::map<std::string, double>& storage, std::string& text)
{
    bool comma = false;
    std::string key;
    std::string value;
    for (std::string::size_type i = 0; i < text.size(); ++i)
    {
        if (text[i] == ',' && !comma)
        {
            comma = true;
            ++i;
        }
        if (!comma)
            key += text[i];
        else
            value += text[i];
    }
    if (key.empty())
        return (void ErrorMessage("")
    double tmp = std::atof(value.c_str());
    storage.insert(std::make_pair(key, tmp));
}

static std::map<std::string, double> file_storage(std::ifstream& file)
{
    std::string text;
    std::map<std::string, double> storage;
    while (std::getline(file, text))
    {
        if (text == "date,exchange_rate")
            continue;
        add_storage(storage, text);
    }

    for (std::map<std::string, double>::const_iterator it = storage.begin(); it != storage.end(); ++it)
        std::cout << "key = " << it->first << "value = " << it->second << std::endl;
    return storage;
}

void BitcoinExchange(char* argv)
{
    std::ifstream file;
    openFile(file, argv);

    std::map<std::string, double> storage = file_storage(file);
}