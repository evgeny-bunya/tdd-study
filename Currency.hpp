#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <utility> // pair
#include <list> // list
#include <memory> // unique_ptr
#include <map> // map
#include <sstream>

class Money;

class Expression
{
    public:
        virtual ~Expression() {}

        virtual Money* reduce(const class Bank*, const std::string& to) const = 0;

        virtual Expression* plus(Expression* addend) const = 0;

        virtual Expression* times(int multiplier) const = 0;

        virtual bool equals(const Money*) const { return false; }

        virtual bool equals(const Expression*) const { return false; }

};

class Money: public Expression
{
        friend class Sum;

    protected:
        const int amount = 0;

        const std::string myCurrency;

    public:
        Money(int initialAmount, const std::string& giveCurrency):
            amount(initialAmount),
            myCurrency(giveCurrency)
        {}

        virtual ~Money() {}

        bool equals(const Expression* rhs) const override
        {
            return rhs->equals(this);
        }

        bool equals(const Money* rhs) const override
        {
            return amount == rhs->amount && myCurrency == rhs->currency();
        }

        Expression* times(int multiplier) const override
        {
            return new Money(amount * multiplier, myCurrency);
        }

        const std::string& currency() const
        {
            return myCurrency;
        }

        Money* reduce(const class Bank*, const std::string& to) const override;

        Expression* plus(Expression* addent) const override;

        static Money* dollar(int initialAmount);

        static Money* franc(int initialAmount);

        bool operator==(const Money& rhs) const
        {
            return equals(&rhs);
        }

        friend std::ostream& operator<<(std::ostream& os, const Money& money)
        {
            os << money.amount << money.myCurrency;
            return os;
        }

};

class Bank
{
        std::map<std::pair<std::string, std::string>, int> rates;

    public:
        Money* reduce(Expression* source, const std::string& to) const;

        int rate(const std::string& from, const std::string& to) const
        {
            if(from == to)
                return 1;

            return rates.at(std::pair<std::string, std::string>(from, to));
        }

        void addRate(const std::string& from, const std::string& to,
                     int nextRate)
        {
            rates[std::pair<std::string, std::string>(from, to)] = nextRate;
        }

};

Money* Money::reduce(const Bank* bank, const std::string& to) const
{
    const int rate = bank->rate(myCurrency, to);
    return new Money(amount / rate, to);
}

class Sum: public Expression
{
        const Expression* augend_ = nullptr;

        const Expression* addend_ = nullptr;

    public:
        Sum(const Expression* augend, const Expression* addend):
            augend_(augend),
            addend_(addend)
        {}

        virtual ~Sum() = default;

        virtual Money* reduce(const Bank* bank, const std::string& to) const override
        {
            std::unique_ptr<Money> reducedAugend(augend_->reduce(bank,
                                                                to));
            std::unique_ptr<Money> reducedAddend(addend_->reduce(bank, to));
            const int amount = reducedAugend->amount + reducedAddend->amount;
            return new Money(amount, to);
        }

        Expression* plus(Expression* addend) const override
        {
            return new Sum(this, addend);
        }

        Expression* times(int multiplier) const override
        {
            return new Sum(augend_->times(multiplier), addend_->times(multiplier));
        }

};

Money* Bank::reduce(Expression* source, const std::string& to) const
{
    return source->reduce(this, to);
}

Expression* Money::plus(Expression* addend) const
{
    return new Sum(this, addend);
}

Money* Money::dollar(int initialAmount)
{
    return new Money(initialAmount, "USD");
}

Money* Money::franc(int initialAmount)
{
    return new Money(initialAmount, "CHF");
}

#endif // CURRENCY_HPP
