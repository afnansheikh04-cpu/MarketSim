#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"

class CsvReader
{
    public:
        static std::vector<Candle> readCandles(const std:: string& filename);
        
};