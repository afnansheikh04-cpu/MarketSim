#include "Portfolio.hpp"

Portfolio::Portfolio(double startingCash, double fee, double slippage)
        : cash(startingCash), longPosition(false), entryPrice(0.0), feePerTrade(fee), slippageRate(slippage), lastTradePnL(0.0)
{
}

bool Portfolio::buy(double price)
{
    // cant buy if already in a trade
    if(longPosition)
    {
        return false;
    }
    double executionPrice = price * (1.0 + slippageRate);
    double totalCost = executionPrice + feePerTrade;
    if(cash<totalCost)
    {
        return false; // cannot afford it
    }
    cash -=totalCost;
    entryPrice = executionPrice;
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

    double executionPrice = price * (1.0 -slippageRate);
    cash +=executionPrice - feePerTrade;
    lastTradePnL = executionPrice - entryPrice - (2.0 * feePerTrade);

    longPosition = false;
    entryPrice =0.0;
    return true;
}

double Portfolio::getLastTradePnL() const
{
    return lastTradePnL;
}

double Portfolio::getEquity(double currentPrice) const
{
    if(longPosition)
    {
        return cash + currentPrice;
    }
    else
    {
        return cash;
    }
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
