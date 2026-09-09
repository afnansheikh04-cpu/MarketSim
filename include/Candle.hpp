#pragma once 
#include <string>
#include <optional>

struct Candle
{
    std::string timestamp;

    double open;
    double high; 
    double low;
    double close; 


    std::optional<double> volume; // volume may exist may not 
};