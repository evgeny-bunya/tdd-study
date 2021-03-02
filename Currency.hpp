 #ifndef CURRENCY_HPP
#define CURRENCY_HPP

enum class Currency
{
    Dollar,
    Franc
};

class Money
{
public:
    bool isEqual(const Money& compare) const
    {
        return (amount == compare.amount) && (currency == compare.currency);
    }
protected:
    int amount;
    Currency currency;
};

class Dollar : public Money
{
public:
    explicit Dollar(int initialValue)
    {
        amount = initialValue;
        currency = Currency::Dollar;
    }
    Dollar times(int multiplicator)
    {
        return Dollar(amount * multiplicator);
    }
};

class Franc : public Money
{
public:
    explicit Franc(int initialValue)
    {
        amount = initialValue;
        currency = Currency::Franc;
    }
    Franc times(int multiplicator)
    {
        return Franc(amount * multiplicator);
    }
};

bool operator==(const Money& lhs, const Money& rhs)
{
    return lhs.isEqual(rhs);
}
bool operator!=(const Money& lhs, const Money& rhs)
{
    return !(lhs ==rhs);
}
#endif // CURRENCY_HPP
