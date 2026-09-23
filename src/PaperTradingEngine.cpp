#include "PaperTradingEngine.hpp"
#include "TradingStrategy.hpp"
#include <iostream>

PaperTradingEngine::PaperTradingEngine(double StartingCash, double feePerTrade, double sillpageRate)
    :portfolio(StartingCash,feePerTrade,sillpageRate)
{}




void PaperTradingEngine::process(const std::vector<Candle>&candles)
{
    if(candles.size() <21)
    {
        std::cout << "Not enough candles formed for paper Trading.\n";
        return;
    }

   

    const Candle& currentCandle = candles.back();

    if(currentCandle.timestamp == lastProcessedTimestamp)
    {
        return;
    }
    lastProcessedTimestamp = currentCandle.timestamp;

    Signal signal = TradingStrategy::evaluate(candles); // run strategy;

    std::cout  << "\n"
               << currentCandle.timestamp
               << " | Close: "
               << currentCandle.close
               << '\n';
            
    if(!portfolio.isLong() && signal == Signal::BUY)
    {
        if(portfolio.buy(currentCandle.close))
        {
            std::cout << "Paper Trade: BUY\n";
        }
    }
    else if(portfolio.isLong() && signal == Signal::SELL)
    {
        if(portfolio.sell(currentCandle.close))
        {
            std::cout << "Paper Trade: SELL"
                     << " | P&L: "
                     << portfolio.getLastTradePnL()
                     << '\n';
        }
    }
    else
    {
        std::cout << "Paper Trade: HOLD\n";
    }

    std::cout << "Position: "
              << (portfolio.isLong() ? "LONG" : "FLAT")
              << '\n';
              
    std::cout << "Equity: "
              << portfolio.getEquity(currentCandle.close)
              << '\n';
}