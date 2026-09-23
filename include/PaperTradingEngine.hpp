#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"
#include "Portfolio.hpp"

class PaperTradingEngine
{
    public: PaperTradingEngine(double startingCash, double feePerTrade, double slippageRate);

    void process(const std::vector<Candle>&candles);

    private : Portfolio portfolio; 
    std:: string lastProcessedTimestamp;
};