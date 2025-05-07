#include "ipv4address.h"

#include <iostream>
#include <vector>
#include <algorithm>

int main(int, char **)
{
    std::vector<IPv4Address> addresses;

    for(std::string line; std::getline(std::cin, line); )
    {
        const auto stop = line.find_first_of('\t');
        const auto substring = stop == std::string::npos ? line : line.substr(0, stop);
        addresses.emplace_back(substring);
    }

    std::sort(addresses.rbegin(), addresses.rend());

    std::vector<const IPv4Address*> filtered_1;
    decltype(filtered_1) filtered_46_70;
    decltype(filtered_1) filtered_any_46;

    for (const auto& a: addresses)
    {
        if (a[0] == 1)
        {
            filtered_1.push_back(&a);
        }
        if (a[0] == 46 and a[1] == 70)
        {
            filtered_46_70.push_back(&a);
        }
        const auto& data = a.data();
        if (std::find(data.begin(), data.end(), 46) != data.end())
        {
            filtered_any_46.push_back(&a);
        }

        // all
        a.print();
    }

    // ^1
    for (const auto a: filtered_1)
    {
        a->print();
    }
    // ^46.70
    for (const auto a: filtered_46_70)
    {
        a->print();
    }
    // *46*
    for (const auto a: filtered_any_46)
    {
        a->print();
    }

    return 0;
}
