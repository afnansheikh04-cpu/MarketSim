#pragma once


class Portfolio
{
public: 
    Portfolio(double startingCash); // construcctor
    bool buy(double price); // buy at this price
    bool sell(double price); // sell at this price
    double getCash() const; // whats my current cash
    double getEntryPrice() const;
    bool isLong() const; // currently holding a position??
private:
    double cash;
    bool longPosition; // are we in a trade yes no
    double entryPrice; // the price bought/sold at

};