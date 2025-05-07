#pragma once

#include <string>
#include <array>
#include <vector>
#include <cstdint> // int types for ubuntu building

class IPv4Address
{
public:
    IPv4Address(const std::string& stringView);
    void print() const noexcept;

    uint8_t operator[](size_t index) const;
    const std::array<uint8_t, 4>& data() const { return m_data; }
    bool operator<(const IPv4Address& other) const noexcept
    {
        return m_data < other.m_data;
    }

private:
    static std::vector<std::string> split(const std::string &str);

    std::array<uint8_t, 4> m_data;
};
