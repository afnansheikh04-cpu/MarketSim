#pragma once
#include <vector>
#include "Candle.hpp"

using std::vector;

class BacktestEngine
{
public:
    static void run(const vector<Candle>& candles);

};
