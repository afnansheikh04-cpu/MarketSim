#include <iostream>
#include <cstdlib>
#include "CsvWriter.hpp"
#include "MarketDataService.hpp"

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
            marketData.getTimeSeries("XAU/USD", "1min", 3);

            CsvWriter::writeCandles("../data/XAUUSD_1min.csv", candles); // the .. at the beginning will go up one file, outside the build file

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