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
    int amount;

};

#endif // CURRENCY_HPP
