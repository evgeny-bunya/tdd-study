#include <cassert>
#include <memory> // unique_ptr

#include "gtest/gtest.h"

#include "Currency.hpp"

TEST(Currency, testMultiplication)
{
    auto fiveDollars = std::make_unique<Dollar>(5);
    Dollar product = fiveDollars->times(2);
    EXPECT_EQ(product.amount, 10);
    product = fiveDollars->times(3);
    EXPECT_EQ(product.amount, 15);
}
