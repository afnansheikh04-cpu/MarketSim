#include <iostream>
#include <cstdlib>
#include "CsvWriter.hpp"
#include "CsvReader.hpp"
#include "MarketDataService.hpp"
#include "Indicators.hpp"

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

        // Request 3 one-minute gold candles
        std::vector<Candle> candles =
            marketData.getTimeSeries("XAU/USD", "1min", 100);

            double sma20 = Indicators::calculateSMA(candles, 20);
            double rsi14 = Indicators::calculateRSI(candles, 14);
            std::cout <<"20-Period SMA: "
                      << sma20
                      << '\n';
            
            std::cout <<"14-Period RSI:"
                    << rsi14
                    << '\n';

            CsvWriter::writeCandles("../data/XAUUSD_1min.csv", candles); // the .. at the beginning will go up one file, outside the build file

        std::vector<Candle> loadedCandles = CsvReader::readCandles("../data/XAUUSD_1min.csv");
        std:: cout << "\n Loaded from CSV: \n";

        for(const Candle& candle : candles)
        {
            std::cout << candle.timestamp
                      << " Open: " << candle.open
                      <<" High: " << candle.high
                      << " Low: " << candle.low
                      << " Close: " << candle.close
                      << '\n';
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}