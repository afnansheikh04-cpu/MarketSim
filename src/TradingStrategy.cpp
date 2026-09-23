#include "TradingStrategy.hpp"
#include "Indicators.hpp"

using namespace std;

Signal TradingStrategy::evaluate( const vector<Candle>& candles)
{
    double sma20 = Indicators:: calculateSMA(candles,20); // sma of last 20 candles
    double rsi14 = Indicators:: calculateRSI(candles, 14); // rsi of last 14 periods
    double latestClose = candles.back().close;

    if(latestClose > sma20 && rsi14<70.0)
    {
        return Signal::BUY; // upward momentum but dont buy if already overbought hence <70
    }
    if(latestClose< sma20 && rsi14 >30.0)
    {
        return Signal:: SELL; // if latest price is below sma and rsi above 30 - not oversold
    }

    return Signal:: HOLD;
}
