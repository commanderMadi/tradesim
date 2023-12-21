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
    static bool compareByTimestamp(OrderBookEntry& order_1,
                                   OrderBookEntry& order_2) {
        return order_1.timestamp < order_2.timestamp;
    }
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2) {
        return e1.price < e2.price;
    }
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2) {
        return e1.price > e2.price;
    }
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};