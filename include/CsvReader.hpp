#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"

using std::string;
using std::vector;

class CsvReader
{
    public:
        static vector<Candle> readCandles(const string& filename); // well be usign the historical candles without copying/modify

};
