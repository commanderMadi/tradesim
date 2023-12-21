#pragma once
#include <vector>

#include "OrderBook.h"
#include "OrderBookEntry.h"
class MerkelMain {
   public:
    MerkelMain() = default;
    /** Call this to start the sim */
    void init();

   private:
    void loadOrderBook();
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
    std::string currentTime;
    OrderBook orderBook{"csvdataset.csv"};
};