#pragma once
#include <string>
#include <optional>

using std::optional;
using std::string;

struct Candle
{
    string timestamp;

    double open;
    double high;
    double low;
    double close;


    optional<double> volume; // volume may exist may not
};
