#pragma once

#include <string>
enum class OrderBookType { ask, bid, unknown };

class OrderBookEntry {
   public:
    /** Create a new OrderBookEntry with the price
     * set to the sent value
     */
    OrderBookEntry(double _price, double _amount, std::string _timestamp,
                   std::string _product, OrderBookType _orderType);
    static OrderBookType stringToOrderBookType(std::string str);
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};