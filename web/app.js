const chartContainer =
    document.getElementById("chart");

const chart =
    LightweightCharts.createChart(
        chartContainer,
        {
            width:
                chartContainer.clientWidth,

            height: 415,

            layout: {
                background: {
                    color: "#0b111b"
                },

                textColor: "#657289"
            },

            grid: {
                vertLines: {
                    color: "#141d2a"
                },

                horzLines: {
                    color: "#141d2a"
                }
            },

            rightPriceScale: {
                borderColor: "#1c2636"
            },

            timeScale: {
                borderColor: "#1c2636",

                timeVisible: true,

                secondsVisible: false
            },

            crosshair: {
                vertLine: {
                    color: "#536078"
                },

                horzLine: {
                    color: "#536078"
                }
            }
        }
    );


const candleSeries =
    chart.addSeries(
        LightweightCharts.CandlestickSeries,
        {
            upColor: "#20d894",

            downColor: "#ff5d6c",

            borderVisible: false,

            wickUpColor: "#20d894",

            wickDownColor: "#ff5d6c"
        }
    );


function generateCandles() {
    const candles = [];
    let currentPrice = 4300;
    let currentTime = Math.floor(Date.now() / 1000) - (80 * 300);
    for (let i = 0; i < 80; i++) {
        const open = currentPrice;
        const change = (Math.random() - 0.45) * 8;
        const close = open + change;
        const high = Math.max(open, close) + Math.random() * 4;
        const low = Math.min(open, close) - Math.random() * 4;
        candles.push({
            time: currentTime,
            open: Number(open.toFixed(2)),
            high: Number(high.toFixed(2)),
            low: Number(low.toFixed(2)),
            close: Number(close.toFixed(2))
        });
        currentPrice = close;
        currentTime += 300;
    }
    return candles;
}

const candles = generateCandles();
candleSeries.setData(candles);
chart.timeScale().fitContent();
let latestCandle = candles[candles.length - 1];

function updatePriceDisplay(candle) {
    document.getElementById("openPrice").textContent = candle.open.toFixed(2);
    document.getElementById("highPrice").textContent = candle.high.toFixed(2);
    document.getElementById("lowPrice").textContent = candle.low.toFixed(2);
    document.getElementById("closePrice").textContent = candle.close.toFixed(2);
    document.getElementById("latestClose").textContent = candle.close.toFixed(2);
}

updatePriceDisplay(latestCandle);

/*
    Simulated live movement.

    Later this gets replaced with
    the candle data from your
    C++ MarketDataService.
*/
setInterval(() => {
    const movement = (Math.random() - 0.5) * 2;
    const newClose = latestCandle.close + movement;
    latestCandle = {
        ...latestCandle,
        high: Math.max(latestCandle.high, newClose),
        low: Math.min(latestCandle.low, newClose),
        close: Number(newClose.toFixed(2))
    };
    candleSeries.update(latestCandle);
    updatePriceDisplay(latestCandle);
}, 2000);

/* TIMEFRAME BUTTONS */
const timeButtons = document.querySelectorAll(".time-button");
timeButtons.forEach(button => {
    button.addEventListener("click", () => {
        timeButtons.forEach(item => item.classList.remove("active"));
        button.classList.add("active");
    });
});

/* EQUITY CHART */
const equityContainer =
    document.getElementById(
        "equityChart"
    );


const equityChart =
    LightweightCharts.createChart(
        equityContainer,
        {
            width:
                equityContainer.clientWidth,

            height: 180,

            layout: {
                background: {
                    color: "#0c121e"
                },

                textColor: "#59677d"
            },

            grid: {
                vertLines: {
                    color: "#141d2a"
                },

                horzLines: {
                    color: "#141d2a"
                }
            },

            rightPriceScale: {
                borderVisible: false
            },

            timeScale: {
                borderVisible: false,

                timeVisible: true
            }
        }
    );


const equitySeries =
    equityChart.addSeries(
        LightweightCharts.LineSeries,
        {
            color: "#397cff",

            lineWidth: 2
        }
    );


function generateEquity() {
    const data = [];
    let value = 10000;
    let time = Math.floor(Date.now() / 1000) - 30 * 300;
    for (let i = 0; i < 30; i++) {
        value += (Math.random() - 0.53) * 10;
        data.push({ time: time, value: Number(value.toFixed(2)) });
        time += 300;
    }
    return data;
}

equitySeries.setData(generateEquity());
equityChart.timeScale().fitContent();

/* RUN BACKTEST BUTTON */
const backtestButton = document.getElementById("runBacktest");
backtestButton.addEventListener("click", () => {
    backtestButton.textContent = "Running...";
    backtestButton.disabled = true;
    setTimeout(() => {
        /*
            These are YOUR actual
            recent MarketSim results.

            Later they will come
            directly from C++.
        */
        document.getElementById("totalReturn").textContent = "-0.23%";
        document.getElementById("winRate").textContent = "0%";
        document.getElementById("drawdown").textContent = "-0.23%";
        document.getElementById("resultPnl").textContent = "-£23.21";
        document.getElementById("resultTrades").textContent = "5";
        document.getElementById("resultWinners").textContent = "0";
        document.getElementById("resultWinRate").textContent = "0%";
        equitySeries.setData(generateEquity());
        equityChart.timeScale().fitContent();
        backtestButton.textContent = "✓ Backtest Complete";
        setTimeout(() => {
            backtestButton.textContent = "▶ Run Backtest";
            backtestButton.disabled = false;
        }, 1500);
    }, 800);
});

/* RESPONSIVE CHARTS */
const resizeObserver = new ResizeObserver(() => {
    chart.applyOptions({ width: chartContainer.clientWidth });
    equityChart.applyOptions({ width: equityContainer.clientWidth });
});
resizeObserver.observe(chartContainer);
