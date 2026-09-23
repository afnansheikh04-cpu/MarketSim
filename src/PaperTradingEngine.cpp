#include "PaperTradingEngine.hpp"
#include "TradingStrategy.hpp"
#include <iostream>

using namespace std;

PaperTradingEngine::PaperTradingEngine(double StartingCash, double feePerTrade, double sillpageRate)
    :portfolio(StartingCash,feePerTrade,sillpageRate)
{}




void PaperTradingEngine::process(const vector<Candle>&candles)
{
    if(candles.size() <21)
    {
        cout << "Not enough candles formed for paper Trading.\n";
        return;
    }



    const Candle& currentCandle = candles.back();

    if(currentCandle.timestamp == lastProcessedTimestamp)
    {
        return;
    }
    lastProcessedTimestamp = currentCandle.timestamp;

    Signal signal = TradingStrategy::evaluate(candles); // run strategy;

    cout  << "\n"
               << currentCandle.timestamp
               << " | Close: "
               << currentCandle.close
               << '\n';

    if(!portfolio.isLong() && signal == Signal::BUY)
    {
        if(portfolio.buy(currentCandle.close))
        {
            cout << "Paper Trade: BUY\n";
        }
    }
    else if(portfolio.isLong() && signal == Signal::SELL)
    {
        if(portfolio.sell(currentCandle.close))
        {
            cout << "Paper Trade: SELL"
                     << " | P&L: "
                     << portfolio.getLastTradePnL()
                     << '\n';
        }
    }
    else
    {
        cout << "Paper Trade: HOLD\n";
    }

    cout << "Position: "
              << (portfolio.isLong() ? "LONG" : "FLAT")
              << '\n';

    cout << "Equity: "
              << portfolio.getEquity(currentCandle.close)
              << '\n';
}
