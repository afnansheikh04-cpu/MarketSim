#include "BacktestEngine.hpp"
#include "TradingStrategy.hpp"
#include <iostream>
#include <vector>

void BacktestEngine::run(const std::vector<Candle>& candles)
{
    bool isLong = false; 

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

        if(!isLong && signal ==  Signal::BUY)
        {
            isLong = true; 
            std:: cout << currentCandle.timestamp
                        << " BUY at: "
                        << currentCandle.close
                        << '\n';
        }
        else if(isLong && signal == Signal::SELL)
        {
            isLong = false;
            std:: cout << currentCandle.timestamp
                        << " SELL at: "
                        << currentCandle.close
                        <<'\n';


        }
    }
    
}