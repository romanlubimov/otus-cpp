#define BOOST_TEST_MODULE test_boost

#include <boost/test/unit_test.hpp>

#include "ipv4address.h"

void firstByteIsTooBig()
{
    IPv4Address("256.4.5.2");
}

void secondByteIsTooBig()
{
    IPv4Address("52.500.5.2");
}

void invalidStringWithSpace()
{
    IPv4Address("52. 500.5.2");
}

void invalidStringWithLeadingDot()
{
    IPv4Address(".52.500.5.2");
}

void correctAddress()
{
    IPv4Address("192.168.0.43");
}

void outOfRange()
{
    IPv4Address address("192.168.0.43");
    address[5];
}

BOOST_AUTO_TEST_SUITE(test_boost)

BOOST_AUTO_TEST_CASE(test_address_validation) {
    BOOST_REQUIRE_THROW(firstByteIsTooBig(), std::runtime_error);
    BOOST_REQUIRE_THROW(secondByteIsTooBig(), std::runtime_error);
    BOOST_REQUIRE_THROW(invalidStringWithSpace(), std::runtime_error);
    BOOST_REQUIRE_THROW(invalidStringWithLeadingDot(), std::runtime_error);
    BOOST_CHECK_NO_THROW(correctAddress());
    BOOST_REQUIRE_THROW(outOfRange(), std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()
