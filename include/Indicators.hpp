#pragma once

#include <vector>

#include "Candle.hpp"

using std::vector;

class Indicators
{
public:
    static double calculateSMA(
        const vector<Candle>& candles,
        int period
    );

    static double calculateRSI(
        const vector<Candle>& candles,
        int period
    );
};
