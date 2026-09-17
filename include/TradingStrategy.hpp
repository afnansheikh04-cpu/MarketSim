#pragma once
#include <vector>
#include "Candle.hpp"
#include "Signal.hpp"

class TradingStrategy // used to evlauate buy sell/hold
{
    public: static Signal evaluate(
        const std::vector<Candle>& candles
    );
};