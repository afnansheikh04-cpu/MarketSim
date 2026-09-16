#include "Indicators.hpp"

#include <stdexcept>

double Indicators::calculateSMA(
    const std::vector<Candle>& candles,
    int period
)
{
    if (period <= 0)
    {
        throw std::invalid_argument("Period must be greater than 0");
    }

    if (candles.size() < static_cast<std::size_t>(period))
    {
        throw std::runtime_error("Not enough candles for SMA");
    }

    double sum = 0.0;

    std::size_t startIndex =
        candles.size() - static_cast<std::size_t>(period); // work out where the final 'period' candles

    for (std::size_t i = startIndex; i < candles.size(); ++i) // add up closing prices
    {
        sum += candles[i].close;
    }

    return sum / period;
}
double Indicators::calculateRSI(
    const std::vector<Candle>& candles,
    int period
)
{
    if (period <= 0)
    {
        throw std::invalid_argument("Period must be greater than 0");
    }

    if (candles.size() < static_cast<std::size_t>(period + 1))
    {
        throw std::runtime_error("Not enough candles for RSI");
    }

    double totalGain = 0.0;
    double totalLoss = 0.0;

    std::size_t startIndex =
        candles.size() - static_cast<std::size_t>(period);

    for (std::size_t i = startIndex; i < candles.size(); ++i)
    {
        double change =
            candles[i].close - candles[i - 1].close;

        if (change > 0)
        {
            totalGain += change;
        }
        else if (change < 0)
        {
            totalLoss += -change;
        }
    }

    double averageGain = totalGain / period;
    double averageLoss = totalLoss / period;

    if (averageGain == 0.0 && averageLoss == 0.0)
    {
        return 50.0;
    }

    if (averageLoss == 0.0)
    {
        return 100.0;
    }

    double relativeStrength =
        averageGain / averageLoss;

    return 100.0 - (100.0 / (1.0 + relativeStrength));
}