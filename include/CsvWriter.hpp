#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"

using std::string;
using std::vector;

class CsvWriter
{
    public:
        static void writeCandles( const string& filename, const vector<Candle>& candles);
};
