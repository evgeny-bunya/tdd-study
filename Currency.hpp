#ifndef CURRENCY_HPP
#define CURRENCY_HPP

class Dollar
{
public:
    explicit Dollar(int initialValue):
        amount(initialValue)
    {

    }
    void times(int multiplicator)
    {
        amount *= multiplicator;
    }
    int amount;

};

#endif // CURRENCY_HPP
