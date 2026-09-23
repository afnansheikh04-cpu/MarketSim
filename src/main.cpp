#include <iostream>
#include <cstdlib>
#include "CsvWriter.hpp"
#include "CsvReader.hpp"
#include "MarketDataService.hpp"
#include "Indicators.hpp"
#include "TradingStrategy.hpp"
#include "BacktestEngine.hpp"
#include "PaperTradingEngine.hpp"
#include <chrono>
#include <thread>

int main()
{
    // Get API key from the environment variable
    const char* apiKey = std::getenv("TWELVE_DATA_API_KEY");

    if (apiKey == nullptr)
    {
        std::cerr << "API key not found." << '\n';
        return 1;
    }

    try
    {
        // Create our market data service
        MarketDataService marketData(apiKey);

        PaperTradingEngine paperTrader(10000.0, 1.0, 0.0001); // startingcash, feeperTrade, slippage

        // Request 3 one-minute gold candles
        std::vector<Candle> candles =
            marketData.getTimeSeries("XAU/USD", "5min", 50);
            BacktestEngine::run(candles);
            double sma20 = Indicators::calculateSMA(candles, 20);
            double rsi14 = Indicators::calculateRSI(candles, 14);
            std::cout <<"20-Period SMA: "
                      << sma20
                      << '\n';
            
            std::cout <<"14-Period RSI:"
                    << rsi14
                    << '\n';

            Signal signal = TradingStrategy::evaluate(candles);
            std::cout << "Signal: ";

            if(signal == Signal::BUY)
            {
                std:: cout << "Buy\n";
            }
            if(signal == Signal::SELL)
            {
                std:: cout << "Sell\n";
            }
            else
            {
                std::cout << "HOLD\n";
            }
            CsvWriter::writeCandles("../data/XAUUSD_5min.csv", candles); // the .. at the beginning will go up one filder, outside the build file

        std::vector<Candle> loadedCandles = CsvReader::readCandles("../data/XAUUSD_5min.csv");

        std:: cout << "\n---- Starting Paper Trading ------\n";

        while(true)
        {
            {
                try
                {
                    {
                        std::vector<Candle> liveCandles = marketData.getTimeSeries("XAU/USD", "5min", 50);
                        paperTrader.process(liveCandles);
                    }
                }
                catch(const std::exception& error)
                {
                    std::cerr << "PaperTradingError: "
                                << error.what()
                                << '\n';
                }

                std::this_thread::sleep_for(std::chrono::seconds(30)); // pauses program for 30 seconds
                
            }
        }
        //std:: cout << "\n Loaded from CSV: \n";

       // for(const Candle& candle : candles)
        //{
       //    std::cout << candle.timestamp
        //              << " Open: " << candle.open
        //              <<" High: " << candle.high
        //              << " Low: " << candle.low
         //             << " Close: " << candle.close
        //              << '\n';
        //}
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}