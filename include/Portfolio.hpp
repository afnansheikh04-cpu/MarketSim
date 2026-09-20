#pragma once


class Portfolio
{
public: 
    Portfolio(double startingCash, double feePerTrade, double slippageRate); // constructor
    bool buy(double price); // buy at this price
    bool sell(double price); // sell at this price
    double getCash() const; // whats my current cash
    double getEntryPrice() const;
    bool isLong() const; // currently holding a position??
    double getLastTradePnL() const; 
    double getEquity(double currentPrice) const;
private:
    double cash;
    bool longPosition; // are we in a trade yes no
    double entryPrice; // the price bought/sold at

    double feePerTrade;
    double slippageRate;
    double lastTradePnL;

};