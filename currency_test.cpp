#include <cassert>
#include <memory> // unique_ptr

#include "gtest/gtest.h"

#include "Currency.hpp"

TEST(Currency, testMultiplication)
{
    ASSERT_TRUE(Money::dollar(10)->equals(Money::dollar(5)->times(2)));
    ASSERT_TRUE(Money::dollar(15)->equals(Money::dollar(5)->times(3)));
    ASSERT_TRUE(Money::franc(10)->equals(Money::franc(5)->times(2)));
    ASSERT_TRUE(Money::franc(15)->equals(Money::franc(5)->times(3)));
}

TEST(Currency, testEquality)
{
    std::unique_ptr<Money> fiveDollars(Money::dollar(5));
    std::unique_ptr<Money> anotherFiveDollars(Money::dollar(5));
    std::unique_ptr<Money> sixDollars(Money::dollar(6));
    std::unique_ptr<Money> fiveFranc(Money::franc(5));

    ASSERT_TRUE(fiveDollars->equals(anotherFiveDollars.get()));
    ASSERT_FALSE(fiveDollars->equals(sixDollars.get()));
    ASSERT_FALSE(fiveFranc->equals(fiveDollars.get()));
}

TEST(Currency, testCurrency)
{
    std::unique_ptr<Money> oneDollar(Money::dollar(1));
    std::unique_ptr<Money> oneFranc(Money::franc(1));

    ASSERT_EQ("USD", oneDollar->currency());
    ASSERT_EQ("CHF", oneFranc->currency());
}

TEST(Currency, testSimpleAddition)
{
    std::unique_ptr<Money> five(Money::dollar(5));
    std::unique_ptr<Money> ten(Money::dollar(10));
    std::unique_ptr<Bank> bank(new Bank);

    std::unique_ptr<Expression> result(five->plus(five.get()));
    Sum* sum = dynamic_cast<Sum*>(result.get());
    std::unique_ptr<Money> reduced(bank->reduce(sum, "USD"));

    ASSERT_TRUE(ten->equals(reduced.get()));
}

TEST(Currency, testReduceSum)
{
    std::unique_ptr<Money> threeDollars(Money::dollar(3));
    std::unique_ptr<Money> fourDollars(Money::dollar(4));
    std::unique_ptr<Expression> sum = std::make_unique<Sum>(threeDollars.get(),
                                                            fourDollars.get());

    auto bank = std::make_unique<Bank>();

    assert(sum);
    std::unique_ptr<Money> result(bank->reduce(sum.get(), "USD"));
    std::unique_ptr<Money> sevenDollars(Money::dollar(7));
    ASSERT_TRUE(sevenDollars->equals(result.get()));
}

TEST(Currency, testReduceMoney)
{
    auto bank = std::make_unique<Bank>();
    std::unique_ptr<Money> oneDollar(Money::dollar(1));
    std::unique_ptr<Money> result(bank->reduce(oneDollar.get(), "USD"));
    ASSERT_TRUE(oneDollar->equals(result.get()));
}

TEST(Currency, testReduceMoneyDifferentCurrency)
{
    auto bank = std::make_unique<Bank>();
    bank->addRate("CHF", "USD", 2);
    std::unique_ptr<Money> twoFrancs(Money::franc(2));
    std::unique_ptr<Money> result(bank->reduce(twoFrancs.get(), "USD"));
    std::unique_ptr<Money> oneDollar(Money::dollar(1));
    ASSERT_TRUE(result->equals(oneDollar.get()));
}

TEST(Currency, identityRate)
{
    std::unique_ptr<Bank> bank;
    ASSERT_EQ(1, bank->rate("USD", "USD"));
}

TEST(Currency, testMixedAddition)
{
    std::unique_ptr<Expression> fiveBucks(Money::dollar(5));
    std::unique_ptr<Expression> tenFrancs(Money::franc(10));
    auto bank = std::make_unique<Bank>();
    bank->addRate("CHF", "USD", 2);
    const auto added = fiveBucks->plus(tenFrancs.get());
    const auto result = bank->reduce(added, "USD");
    std::unique_ptr<Money> tenBucks(Money::dollar(10));
    ASSERT_TRUE(result->equals(tenBucks.get()));
}

TEST(Currency, testSumTimes)
{
    std::unique_ptr<Expression> fiveBucks(Money::dollar(5));
    std::unique_ptr<Expression> tenFrancs(Money::franc(10));
    auto bank = std::make_unique<Bank>();
    bank->addRate("CHF", "USD", 2);
    std::unique_ptr<Expression> sumOrig(new Sum(fiveBucks.get(), tenFrancs.get()));
    std::unique_ptr<Expression> sum(sumOrig->times(2));
    std::unique_ptr<Money> result(bank->reduce(sum.get(), "USD"));
    std::unique_ptr<Money> twentyBucks(Money::dollar(20));
    ASSERT_EQ(*twentyBucks, *result);
}
