#ifndef CURRENCY_HPP
#define CURRENCY_HPP

class Dollar
{
public:
    explicit Dollar(int initialValue):
        amount(initialValue)
    {

    }
    Dollar times(int multiplicator)
    {
        return Dollar(amount * multiplicator);
    }
    bool isEqual(const Dollar& compare) const
    {
        return (amount == compare.amount);
    }
private:
    int amount;
};

bool operator==(const Dollar& lhs, const Dollar& rhs)
{
    return lhs.isEqual(rhs);
}
bool operator!=(const Dollar& lhs, const Dollar& rhs)
{
    return !lhs.isEqual(rhs);
}

#endif // CURRENCY_HPP
