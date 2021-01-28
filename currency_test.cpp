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
    //EXPECT_EQ(*std::make_unique<Dollar>(7), *std::make_unique<Dollar>(7));
    EXPECT_NE(*std::make_unique<Dollar>(7), *std::make_unique<Dollar>(8));
}

