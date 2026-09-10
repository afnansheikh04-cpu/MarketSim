#include "MarketDataService.hpp"
#include <curl/curl.h>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <algorithm>

static size_t writeCallback( // data received by the api
    void* contents,
    size_t size,
    size_t nmemb, 
    void* userData
)
{
    size_t totalSize = size * nmemb; // calcuatles total number of bytes received in this chunk

    std:: string* response = static_cast<std::string*>(userData); // convert userdata into a string

    response-> append( // appends the received data into the response string
        static_cast<char*>(contents),
        totalSize

    );

    return totalSize;
}

// constructor - stores the api inside the object
MarketDataService::MarketDataService(
const std:: string &key // value passed into the constructor
) : apiKey(key) // init
{
}

std:: vector<Candle> MarketDataService::getTimeSeries(const std:: string& symbol,const std:: string & interval,int outputSize)    const
{
    // create a CURL handle for the HTTP request

    CURL* curl = curl_easy_init();

    if(!curl)
    {
        throw std:: runtime_error("Failed to initialise CURL");
    }

    std:: string response; // this hodls the json response from the api 

    char* encodedSymbol = curl_easy_escape(curl, symbol.c_str(), 0); // encode symbols inside the URL
    
    std:: string url = 
        "https://api.twelvedata.com/time_series"
        "?symbol=" + std::string(encodedSymbol) +
        "&interval=" + interval +
        "&outputsize=" + std::to_string(outputSize) +
        "&apikey=" + apiKey; // all these parameters are added to the URL were creating

    curl_free(encodedSymbol); // free memory created by the curl easy escape

    // Tell CURL which URL to request
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Tell CURL which function should handle incoming data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    // Tell CURL to store incoming data inside response
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the actual HTTP request
    CURLcode result = curl_easy_perform(curl);

    // Clean up CURL resources
    curl_easy_cleanup(curl);

    if(result != CURLE_OK)
    {
        throw std:: runtime_error( curl_easy_strerror(result));
    }

    nlohmann::json data = nlohmann::json::parse(response); // Parse the raw JSON response

    if(!data.contains("values"))
    {
        throw std::runtime_error("No market data returned");
    }

    std::vector< Candle>  candles; // store teh candel objects
    
    for(const auto& value : data["values"]) //auto finds 
    {
        Candle candle;
        candle.timestamp = value["datetime"].get<std::string>();
        candle.open = std::stod(value["open"].get<std::string>()); // stod means string to double 
        candle.high = std::stod(value["high"].get<std::string>());
        candle.low = std::stod(value["low"].get<std::string>());
        candle.close = std::stod(value["close"].get<std::string>());

        if(value.contains("volume"))
        {
            candle.volume = std::stod(value["volume"].get<std::string>());
        }
        candles.push_back(candle);

    }

    std::reverse(candles.begin(),candles.end());

    return candles;



}