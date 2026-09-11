#include "CsvReader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>


std::vector<Candle> CsvReader::readCandles(const std:: string& filename)
{
    std:: ifstream file(filename); // open file

    if(!file.is_open())
    {
        throw std::runtime_error("Could not open CSV file");
    }

    std:: vector<Candle> candles;
    std:: string line;
    std::getline(file, line); // stores header line inside here 

    while(std::getline(file,line)) // keep looping whilst there is aline to read 
    {
        std::stringstream row(line);

        std::string timestamp;
        std::string open;
        std::string high;
        std::string low;
        std::string close;
        std::string volume; // create empty strings for each 


        // now split 
        std::getline(row, timestamp, ',');
        std::getline(row, open, ',');
        std::getline(row, high, ',');
        std::getline(row, low, ',');
        std::getline(row, close, ',');
        std::getline(row, volume, ',');

        Candle candle;

        candle.timestamp = timestamp;
        candle.open = std::stod(open);
        candle.high = std::stod(high);
        candle.low = std::stod(low);
        candle.close = std::stod(close);

        if(!volume.empty())
        {
            candle.volume = std::stod(volume);
        }

        candles.push_back(candle); // add this candle to the end of the vector candle
    }
    return candles;



}