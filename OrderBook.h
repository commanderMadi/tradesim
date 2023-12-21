#pragma once

#include <string>
#include <vector>

#include "CSVReader.h"
#include "OrderBookEntry.h"

class OrderBook {
   public:
    /** Construct, reading a csv data file*/
    OrderBook(std::string filename);
    std::size_t getOrderSize() const { return orders.size(); }
    /** return a vector of all known products in the dataset*/
    std::vector<std::string> getKnownProducts();
    /** return vector of ordersing according to given filters*/
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    /** return the price of the highest bid in the sent set*/
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    /** return the price of the lowest bid in the sent set*/
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    /** returns the earliest time in the orders book*/
    std::string getEarliestTime();
    /** returns the next time after the sent time in the orders book*/
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);

   private:
    std::vector<OrderBookEntry> orders;
};