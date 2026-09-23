#include "CsvReader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;


vector<Candle> CsvReader::readCandles(const string& filename)
{
    ifstream file(filename); // open file

    if(!file.is_open())
    {
        throw runtime_error("Could not open CSV file");
    }

    vector<Candle> candles;
    string line;
    getline(file, line); // stores header line inside here

    while(getline(file,line)) // keep looping whilst there is aline to read
    {
        stringstream row(line);

        string timestamp;
        string open;
        string high;
        string low;
        string close;
        string volume; // create empty strings for each


        // now split
        getline(row, timestamp, ',');
        getline(row, open, ',');
        getline(row, high, ',');
        getline(row, low, ',');
        getline(row, close, ',');
        getline(row, volume, ',');

        Candle candle;

        candle.timestamp = timestamp;
        candle.open = stod(open);
        candle.high = stod(high);
        candle.low = stod(low);
        candle.close = stod(close);

        if(!volume.empty())
        {
            candle.volume = stod(volume);
        }

        candles.push_back(candle); // add this candle to the end of the vector candle
    }
    return candles;



}
