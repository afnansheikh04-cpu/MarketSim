#pragma once
#include <string>
#include <vector>
#include "Candle.hpp"

using std::string;
using std::vector;

class MarketDataService
{
    public:
        MarketDataService(const string & apiKey); // constructor - pass in api key

        vector<Candle> getTimeSeries( // function to fetch market data
            const string & symbol, // commodity or whatever it may be
            const string & interval, // 1 min candle 1 day candlet etc
            int outputSize // how many candles we want from the api
        ) const; // const at the end means object wont be altered just used

        // this initially returns a raw json response

    private:
        string apiKey; // api key is stored privately -- variable to store the api key


};
