#include "BacktestEngine.hpp"
#include "TradingStrategy.hpp"
#include <iostream>
#include <vector>
#include "Portfolio.hpp"

using namespace std;

void BacktestEngine::run(const vector<Candle>& candles)
{
    const double startingCash = 10000.0;
    const double feePerTrade = 1.0;
    const double slippageRate = 0.0001; // 0.01%
    Portfolio portfolio(startingCash,feePerTrade,slippageRate);


    int totalTrades =0;
    int winningTrades = 0;
    int losingTrades = 0; // used to keep track of trades
    double peakEquity = startingCash;
    double maxDrawdown = 0.0;


    const size_t minimumCandles = 20; // need at least 20 candles for SMA

    if(candles.size() < minimumCandles)
    {
        cout << "Not enough Candles to run Backtest. \n";
        return;
    }

    for(size_t i=minimumCandles; i<=candles.size(); i++)
    {
        vector<Candle> history(candles.begin(),
        candles.begin() + static_cast<ptrdiff_t>(i)) ;//create new vector of only old candles after each candle
        //containing the candles in there so far
        // candles.begin() points to the first element in the vecor

        Signal signal = TradingStrategy::evaluate(history); //eval using old canldes only

        const Candle& currentCandle = history.back();

        if(!portfolio.isLong() && signal ==  Signal::BUY)
        {
            if(portfolio.buy(currentCandle.close))
            {
                cout << currentCandle.timestamp
                    << " BUY at: "
                    << currentCandle.close
                    << '\n';
            }

        }
        else if(portfolio.isLong() && signal == Signal::SELL)
        {

            double entryPrice = portfolio.getEntryPrice();
            double exitPrice = currentCandle.close;


            if(portfolio.sell(currentCandle.close))
            {
                double tradePnl = portfolio.getLastTradePnL();

                totalTrades++;
                if(tradePnl > 0)
                {
                    winningTrades++;
                }
                else if(tradePnl <0)
                {
                    losingTrades++;
                }

                cout << currentCandle.timestamp
                    << " SELL at: "
                    << exitPrice
                    << " | P&L "
                    << tradePnl
                    <<'\n';

            }
        }

        double currentEquity = portfolio.getEquity(currentCandle.close);

        if(currentEquity>peakEquity)
        {
            peakEquity = currentEquity;
        }

        double drawdown = ((peakEquity - currentEquity) / peakEquity) *100.0;

        if(drawdown>maxDrawdown)
        {
            maxDrawdown = drawdown;
        }
    }
    if(portfolio.isLong())
    {
        double entryPrice = portfolio.getEntryPrice();
        double exitPrice = candles.back().close;

        portfolio.sell(exitPrice);
        double tradePnl = portfolio.getLastTradePnL();

        totalTrades++;
        if(tradePnl>0)
        {
            winningTrades++;
        }
        else if(tradePnl<0)
        {
            losingTrades++;
        }

        cout << candles.back().timestamp
                  << " FINAL SELL at: "
                  << exitPrice
                  << " | P&L: "
                  <<tradePnl
                  << '\n';

        double finalEquity = portfolio.getCash();

        if(finalEquity> peakEquity)
        {
            peakEquity = finalEquity;
        }
        double finalDrawdown = ((peakEquity - finalEquity) / peakEquity) *100.0;

        if(finalDrawdown > maxDrawdown)
        {
            maxDrawdown = finalDrawdown;
        }
    }

    double finalCash = portfolio.getCash();
    double totalPnl = finalCash - startingCash;
    double totalReturn = (totalPnl / startingCash) *100;
    double winRate =0;

    if(totalTrades>0)
    {
        winRate = (static_cast<double>(winningTrades) / totalTrades) *100; // static cast double turns int into double
    }

    cout << "\n--- Backtest Summary ---\n";
    cout << "Starting Cash: " << startingCash << '\n';
    cout << "Final Cash: " << finalCash << '\n';
    cout << "Total P&L: " << totalPnl << '\n';
    cout << "Total Return: " << totalReturn << "%\n";
    cout << "Total Trades: " << totalTrades << '\n';
    cout << "Winning Trades: " << winningTrades << '\n';
    cout << "Losing Trades: " << losingTrades << '\n';
    cout << "Win Rate: " << winRate << "%\n";
    cout << "Max Drawdown: " << maxDrawdown << "%\n";

}
