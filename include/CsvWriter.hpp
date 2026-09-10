#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"

class CsvWriter
{
    public:
        static void writeCandles( const std::string& filename, const std::vector<Candle>& candles);
};