#include "Portfolio.hpp"

Portfolio::Portfolio(double startingCash)
        : cash(startingCash), longPosition(false), entryPrice(0.0)
{
}

bool Portfolio::buy(double price)
{
    // cant buy if already in a trade
    if(longPosition)
    {
        return false;
    }
    if(cash<price)
    {
        return false; // cannot afford it
    }
    cash -=price;
    entryPrice = price;
    longPosition = true;

    return true;
}
bool Portfolio::sell(double price)
{
    // cant buy if already in a trade
    if(!longPosition)
    {
        return false;
    }
    cash +=price;
    entryPrice = price;
    longPosition = false;

    return true;
}
double Portfolio::getCash() const
{
    return cash;
}
bool Portfolio::isLong() const
{
    return longPosition;
}
double Portfolio::getEntryPrice() const
{
    return entryPrice;
}
