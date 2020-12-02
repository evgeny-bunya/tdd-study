#include <cassert>
#include <memory> // unique_ptr

#include "gtest/gtest.h"

#include "Currency.hpp"

TEST(Currency, testMultiplication)
{
    auto fiveDollars = std::make_unique<Dollar>(5);
    fiveDollars->times(2);
    EXPECT_EQ(fiveDollars->amount, 10);
}
