
#include "MerkelMain.h"

#include <iostream>
#include <vector>

#include "CSVReader.h"
#include "OrderBook.h"

void MerkelMain::init() {
    loadOrderBook();

    int input;
    currentTime = orderBook.getEarliestTime();

    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook() {
    // std::cout << "Reading this from OrderBook. Total entries in Market: "
    //           << orderBook.getOrderSize() << " entries" << std::endl;

    // /** Testing if all known products in the dataset are returned properly*/
    // orderBook.getKnownProducts();
    // /** Testing returned orders based on given filters*/
    // orderBook.getOrders(OrderBookType::ask, "BTC/USDT",
    //                     "2020/03/17 17:01:24.884492");
}

void MerkelMain::printMenu() {
    std::cout << "1: Print help " << std::endl;
    std::cout << "2: Print Exchange Stats " << std::endl;
    std::cout << "3: Make an Offer " << std::endl;
    std::cout << "4: Make a Bid " << std::endl;
    std::cout << "5: Print Wallet " << std::endl;
    std::cout << "6: Continue " << std::endl;
    std::cout << "============== " << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp() {
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void MerkelMain::printMarketStats() {
    std::vector<std::string> products = orderBook.getKnownProducts();
    for (const std::string& product : products) {
        std::cout << "Product: " << product << std::endl;
        std::vector<OrderBookEntry> entries =
            orderBook.getOrders(OrderBookType::ask, product, currentTime);
        std::cout << "Asks for this timestamp: " << entries.size() << std::endl;
        std::cout << "Max Ask: " << orderBook.getHighPrice(entries)
                  << std::endl;
        std::cout << "Min Ask: " << orderBook.getLowPrice(entries) << std::endl;
    }
}
void MerkelMain::enterAsk() {
    std::cout << "Enter the amount as: product,price,amount eg ETH/BTC,200,0.5"
              << std::endl;
    std::string input;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterAsk => Bad Input. Please stick "
                     "to the specified format"
                  << std::endl;
    } else {
        try {
            OrderBookEntry obe =
                CSVReader::inputToOBE(tokens[1], tokens[2], currentTime,
                                      tokens[0], OrderBookType::ask);
            orderBook.insertOrder(obe);
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk => Bad input. Choose from "
                         "available products and enter "
                         "amount and price"
                      << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
}
void MerkelMain::enterBid() {
    std::cout << "Enter the amount as: product,price,amount eg ETH/BTC,200,0.5"
              << std::endl;
    std::string input;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterBid => Bad Input. Please stick "
                     "to the specified format"
                  << std::endl;
    } else {
        try {
            OrderBookEntry obe =
                CSVReader::inputToOBE(tokens[1], tokens[2], currentTime,
                                      tokens[0], OrderBookType::bid);
            orderBook.insertOrder(obe);
        } catch (const std::exception& e) {
            std::cout << "MerkelMain::enterBid => Bad input. Choose from "
                         "available products and enter "
                         "amount and price"
                      << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
}
void MerkelMain::printWallet() { std::cout << "Wallet is empty!" << std::endl; }

void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to next frame!." << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::processUserOption(int userOption) {
    if (userOption == 0) {
        std::cout << "Invalid choice. Choose 1 - 6\n";
    }

    if (userOption == 1) {
        printHelp();
    }
    if (userOption == 2) {
        printMarketStats();
    }
    if (userOption == 3) {
        enterAsk();
    }
    if (userOption == 4) {
        enterBid();
    }
    if (userOption == 5) {
        printWallet();
    }
    if (userOption == 6) {
        gotoNextTimeframe();
    }
}

int MerkelMain::getUserOption() {
    std::string line;
    std::getline(std::cin, line);
    int userOption;
    std::cout << "Please enter a number from 1 to 6" << std::endl;
    try {
        userOption = std::stoi(line);
    } catch (const std::exception& e) {
        std::cout
            << "MerkelMain::getUserOption: Bad input. Only 1 to 6 is allowed"
            << std::endl;
    }
    std::cout << "You chose " << userOption << " ." << std::endl;
    return userOption;
}