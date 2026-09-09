#pragma once
#include <string>

class MarketDataService
{
    public:
        MarketDataService(const std::string & apiKey); // construcrot - pass in api key 

        std::string getTimeSeries( // function to fetch market data
            const std:: string & symbol, // commodity or whatever it may be 
            const std:: string & inverval, // 1 min candle 1 day candlet etc
            int outputSize // how many candles we want from the api
        ) const; // const at the end means object wont be altered just used

        // this initially returns a raw json response

    private:
        std:: string apiKey; // api key is stored privately -- variable to store the api key 


};