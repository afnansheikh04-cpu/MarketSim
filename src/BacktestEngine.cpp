#include "BacktestEngine.hpp"
#include "TradingStrategy.hpp"
#include <iostream>
#include <vector>
#include "Portfolio.hpp"

void BacktestEngine::run(const std::vector<Candle>& candles)
{
    Portfolio portfolio(10000.0);
    

    const std::size_t minimumCandles = 20; // need at least 20 candles for SMA

    if(candles.size() < minimumCandles)
    {
        std::cout << "Not enough Candles to run Backtest. \n";
        return;
    }

    for(std::size_t i=minimumCandles; i<=candles.size(); i++)
    {
        std::vector<Candle> history(candles.begin(),
        candles.begin() + static_cast<std::ptrdiff_t>(i)) ;//create new vector of only old candles after each candle
        //containing the candles in there so far
        // candles.begin() points to the first element in the vecor

        Signal signal = TradingStrategy::evaluate(history); //eval using old canldes only

        const Candle& currentCandle = history.back();

        if(!portfolio.isLong() && signal ==  Signal::BUY)
        {
            if(portfolio.buy(currentCandle.close))
            {
                std:: cout << currentCandle.timestamp
                    << " BUY at: "
                    << currentCandle.close
                    << '\n';
            }
            

        }
        else if(portfolio.isLong() && signal == Signal::SELL)
        {
            
            double entryPrice = portfolio.getEntryPrice();
            double exitPrice = currentCandle.close;


            if(portfolio.sell(currentCandle.close))
            {
                double tradePnl = exitPrice - entryPrice;

                std:: cout << currentCandle.timestamp
                    << " SELL at: "
                    << exitPrice
                    << " | P&L "
                    << tradePnl
                    <<'\n';

            }
        }
    }
    if(portfolio.isLong())
    {
        double entryPrice = portfolio.getEntryPrice();
        double exitPrice = candles.back().close;
        
        portfolio.sell(exitPrice);
        double tradePnl = exitPrice - entryPrice;

        std::cout << candles.back().timestamp
                  << " FINAL SELL at: "
                  << exitPrice
                  << " | P&L: "
                  <<tradePnl
                  << '\n';
    }
    double startingCash = 10000.0;
    double finalCash = portfolio.getCash();
    double totalPnl = finalCash - startingCash;

    std::cout << "\n--- Backtest Summary ---\n";
    std::cout << "Starting Cash: " << startingCash << '\n';
    std::cout << "Final Cash: " << finalCash << '\n';
    std::cout << "Total P&L: " << totalPnl << '\n';
    
}