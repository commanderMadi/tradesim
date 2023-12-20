#include "OrderBookEntry.h"

#include <string>

OrderBookEntry::OrderBookEntry(double _price, double _amount,
                               std::string _timestamp, std::string _product,
                               OrderBookType _orderType)
    : price(_price),
      amount(_amount),
      timestamp(_timestamp),
      product(_product),
      orderType(_orderType){};

OrderBookType OrderBookEntry::stringToOrderBookType(std::string type) {
    if (type == "ask") {
        return OrderBookType::ask;
    }
    if (type == "bid") {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}