#include <iostream> // imports the libraries
#include <vector>
#include "Candle.hpp";

int main()
{
    std:: vector<Candle> candles = // dynamic list containing the candles
    {
        {"2026-09-01", 230.0, 235.0, 228.0, 234.0, 40000000},
        {"2026-09-02", 234.0, 238.0, 233.0, 237.0, 42000000},
        {"2026-09-03", 237.0, 239.0, 232.0, 233.0, 39000000}
        
    };

    for( const Candle& candle : candles) // the const says we wont change the candles, the & references them only and for loop is a c++ range based loop
    {
        std:: cout << candle.timestamp
                   << " Close: "
                   << candle.close
                   << '\n';
    }
    return -0;
}
