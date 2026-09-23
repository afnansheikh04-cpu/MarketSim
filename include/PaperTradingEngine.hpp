#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"
#include "Portfolio.hpp"

using std::string;
using std::vector;

class PaperTradingEngine
{
    public: PaperTradingEngine(double startingCash, double feePerTrade, double slippageRate);

    void process(const vector<Candle>&candles);

    private : Portfolio portfolio;
    string lastProcessedTimestamp;
};
