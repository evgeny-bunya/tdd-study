#include <cassert>
#include <memory> // unique_ptr

#include "gtest/gtest.h"

#include "Currency.hpp"

TEST(Currency, testMultiplication)
{
    auto fiveDollars = std::make_unique<Dollar>(5);
    EXPECT_EQ(fiveDollars->times(2), *std::make_unique<Dollar>(10));
    EXPECT_EQ(fiveDollars->times(3), *std::make_unique<Dollar>(15));
}

TEST(Currency, equalityCheck)
{
    EXPECT_EQ(*std::make_unique<Dollar>(7), *std::make_unique<Dollar>(7));
    EXPECT_NE(*std::make_unique<Dollar>(7), *std::make_unique<Dollar>(8));
    EXPECT_EQ(*std::make_unique<Franc>(7), *std::make_unique<Franc>(7));
    EXPECT_NE(*std::make_unique<Franc>(7), *std::make_unique<Franc>(8));
    EXPECT_NE(*std::make_unique<Franc>(7), *std::make_unique<Dollar>(7));
}

TEST(Currency, francTestMultiplication)
{
    auto fiveFrancs = std::make_unique<Franc>(5);
    EXPECT_EQ(fiveFrancs->times(2), *std::make_unique<Franc>(10));
    EXPECT_EQ(fiveFrancs->times(3), *std::make_unique<Franc>(15));
}


