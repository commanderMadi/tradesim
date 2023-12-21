#include "OrderBook.h"

#include <iostream>
#include <map>
#include <utility>

OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
    /**Create a map between each product string and a boolean that states
     * whether it exists or not*/
    std::map<std::string, bool> prodMap;
    for (const OrderBookEntry& order : orders) {
        prodMap[order.product] = true;
    }
    /** Push products according to their mapped values*/
    std::vector<std::string> products;
    for (const auto& productStringBoolPair : prodMap) {
        products.push_back(productStringBoolPair.first);
    }
    // /** Print available products by name*/
    // for (const std::string& product : products) {
    //     std::cout << "Product: " << product << std::endl;
    // }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp) {
    std::vector<OrderBookEntry> filteredOrders;
    for (const OrderBookEntry& order : orders) {
        if (order.orderType == type && order.product == product &&
            order.timestamp == timestamp) {
            filteredOrders.push_back(order);
        }
    }
    // /** Looping over filtered orders to print them out*/
    // for (const OrderBookEntry& order : filteredOrders) {
    //     std::cout << "Order price: " << order.price << "Order product "
    //               << order.product << std::endl;
    // }
    return filteredOrders;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
    double max{orders[0].price};
    for (const OrderBookEntry& order : orders) {
        if (order.price > max) max = order.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
    double min{orders[0].price};
    for (const OrderBookEntry& order : orders) {
        if (order.price < min) min = order.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime() { return orders[0].timestamp; }
std::string OrderBook::getNextTime(std::string timestamp) {
    std::string next_timestamp = "";
    for (const OrderBookEntry& order : orders) {
        if (timestamp < order.timestamp) {
            next_timestamp = order.timestamp;
            break;
        }
    }
    if (next_timestamp == "") {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}
void OrderBook::insertOrder(OrderBookEntry& order) {
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}
