#pragma once

#include <vector>

#include "Candle.hpp"

class Indicators
{
public:
    static double calculateSMA(
        const std::vector<Candle>& candles,
        int period
    );

    static double calculateRSI(
        const std::vector<Candle>& candles,
        int period
    );
};