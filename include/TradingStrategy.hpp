#pragma once
#include <vector>
#include "Candle.hpp"
#include "Signal.hpp"

using std::vector;

class TradingStrategy // used to evlauate buy sell/hold
{
    public: static Signal evaluate(
        const vector<Candle>& candles
    );
};
