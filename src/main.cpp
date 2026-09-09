#include <iostream>
#include <cstdlib>

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
        std::string response =
            marketData.getTimeSeries("XAU/USD", "1min", 3);

        // Print the raw JSON response
        std::cout << response << '\n';
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}