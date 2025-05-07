#include "ipv4address.h"

#include <iostream>

constexpr char BYTES_DELIMITER = '.';
constexpr uint8_t BYTES_COUNT = 4;

IPv4Address::IPv4Address(const std::string &str)
{
    const auto vector = split(str);
    if (vector.size() != BYTES_COUNT)
    {
        throw std::runtime_error("Invalid address \"" + str + "\": wrong byte number");
    }

    auto inByteRange = [](int number) -> bool { return number >= 0 and number <= 255; };

    for(int8_t i = 0; i < BYTES_COUNT; ++i)
    {
        int parsedNumber = 0;

        try {
            parsedNumber = std::stoi( vector[i] );
        } catch (std::exception& e) {
            throw std::runtime_error(std::string("Invalid address \"" + str + "\": std::stoi() failed with ") + e.what());
        }

        if (not inByteRange(parsedNumber))
        {
            throw std::runtime_error("Invalid address \"" + str + "\": not in byte range (0-255)");
        }

        m_data[i] = parsedNumber;
    }
}

void IPv4Address::print() const noexcept
{
    for(int8_t i = 0; i < BYTES_COUNT; ++i)
    {
        std::cout << static_cast<int>(m_data[i]);
        if (i+1 < BYTES_COUNT)
        {
            std::cout << BYTES_DELIMITER;
        }
    }
    std::cout << std::endl;
}

uint8_t IPv4Address::operator[](size_t index) const
{
    if (index > BYTES_COUNT-1)
    {
        throw std::overflow_error("IPv4Address::operator[] accept range 0-3");
    }
    return m_data[index];
}

std::vector<std::string> IPv4Address::split(const std::string &str)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(BYTES_DELIMITER);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(BYTES_DELIMITER, start);
    }

    r.push_back(str.substr(start));

    return r;
}
