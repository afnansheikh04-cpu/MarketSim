#include "CsvWriter.hpp"
#include <fstream> // to write
#include <stdexcept> // error handling

void CsvWriter::writeCandles(const std::string&filename, const std::vector<Candle>& candles)
{
    std:: ofstream file(filename); //output file stream

    if(!file.is_open())
    {
        throw std:: runtime_error("Could not open CSV file");
    }

    file << "timestamp,open,high,low,close,volume \n"; // file << writes directly into file rather than outputting it to terminal

    for(const Candle& candle: candles)
    {
        file << candle.timestamp << ","
            << candle.open << ","
            << candle.high << ","
            << candle.low << ","
            << candle.close << ","; 
        
        if(candle.volume.has_value())
        {
            file << candle.volume.value();
        }
        file << "\n";

    }
}