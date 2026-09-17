#pragma once
#include <vector>
#include "Candle.hpp"

class BacktestEngine
{
public:
    static void run(const std::vector<Candle>& candles);

};