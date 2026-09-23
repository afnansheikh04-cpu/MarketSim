#include "MarketDataService.hpp"
#include <curl/curl.h>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <algorithm>

using namespace std;

static size_t writeCallback( // data received by the api
    void* contents,
    size_t size,
    size_t nmemb,
    void* userData
)
{
    size_t totalSize = size * nmemb; // calcuatles total number of bytes received in this chunk

    string* response = static_cast<string*>(userData); // convert userdata into a string

    response-> append( // appends the received data into the response string
        static_cast<char*>(contents),
        totalSize

    );

    return totalSize;
}

// constructor - stores the api inside the object
MarketDataService::MarketDataService(
const string &key // value passed into the constructor
) : apiKey(key) // init
{
}

vector<Candle> MarketDataService::getTimeSeries(const string& symbol,const string & interval,int outputSize)    const
{
    // create a CURL handle for the HTTP request

    CURL* curl = curl_easy_init();

    if(!curl)
    {
        throw runtime_error("Failed to initialise CURL");
    }

    string response; // this hodls the json response from the api

    char* encodedSymbol = curl_easy_escape(curl, symbol.c_str(), 0); // encode symbols inside the URL

    string url =
        "https://api.twelvedata.com/time_series"
        "?symbol=" + string(encodedSymbol) +
        "&interval=" + interval +
        "&outputsize=" + to_string(outputSize) +
        "&timezone=Europe/London" +
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
        throw runtime_error( curl_easy_strerror(result));
    }

    nlohmann::json data = nlohmann::json::parse(response); // Parse the raw JSON response

    if(!data.contains("values"))
    {
        throw runtime_error("No market data returned");
    }

    vector< Candle>  candles; // store teh candel objects

    for(const auto& value : data["values"]) //auto finds
    {
        Candle candle;
        candle.timestamp = value["datetime"].get<string>();
        candle.open = stod(value["open"].get<string>()); // stod means string to double
        candle.high = stod(value["high"].get<string>());
        candle.low = stod(value["low"].get<string>());
        candle.close = stod(value["close"].get<string>());

        if(value.contains("volume"))
        {
            candle.volume = stod(value["volume"].get<string>());
        }
        candles.push_back(candle);

    }

    reverse(candles.begin(),candles.end());

    return candles;



}
