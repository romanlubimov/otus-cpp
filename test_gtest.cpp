#include <gtest/gtest.h>
#include "ipv4address.h"

TEST(IPv4AddressTest, FirstByteIsTooBig) {
    EXPECT_THROW(IPv4Address("256.4.5.2"), std::runtime_error);
}

TEST(IPv4AddressTest, SecondByteIsTooBig) {
    EXPECT_THROW(IPv4Address("52.500.5.2"), std::runtime_error);
}

TEST(IPv4AddressTest, InvalidStringWithSpace) {
    EXPECT_THROW(IPv4Address("52. 500.5.2"), std::runtime_error);
}

TEST(IPv4AddressTest, InvalidStringWithLeadingDot) {
    EXPECT_THROW(IPv4Address(".52.500.5.2"), std::runtime_error);
}

TEST(IPv4AddressTest, CorrectAddress) {
    EXPECT_NO_THROW(IPv4Address("192.168.0.43"));
}

TEST(IPv4AddressTest, OutOfRange) {
    IPv4Address address("192.168.0.43");
    EXPECT_THROW(address[5], std::overflow_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
