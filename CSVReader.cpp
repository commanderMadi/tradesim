//
//  CSVReader.cpp
//  merkelex
//
//  Created by Ahmed Magdy on 2023/12/10.
//

#include "CSVReader.h"

#include <iostream>
#include <string>
#include <vector>

CSVReader::CSVReader(){};
std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) {
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFilename};
    std::string line;

    if (csvFile.is_open()) {
        std::string line;
        while (getline(csvFile, line)) {
            try {
                std::vector<std::string> tokens = tokenise(line, ',');
                OrderBookEntry entry = stringsToOBE(tokens);
                entries.push_back(entry);
            } catch (std::exception& e) {
                // std::cout << "CSVReader::readCSV bad data" << std::endl;
            }
        }
    }
    std::cout << "Total entries read: " << entries.size() << std::endl;
    return entries;
};

std::vector<std::string> CSVReader::tokenise(std::string csvLine,
                                             char separator) {
    std::vector<std::string> tokens;
    std::string token;
    signed int start, end;

    start = csvLine.find_first_not_of(separator, 0);

    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;

        if (end >= 0) {
            token = csvLine.substr(start, end - start);
        } else {
            token = csvLine.substr(start, csvLine.length() - start);
        }

        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);
    return tokens;
};
OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;

    if (tokens.size() != 5) {
        throw std::runtime_error("Bad line. Skipping to next line.");
    }

    try {
        timestamp = tokens[0];
        product = tokens[1];
        orderType = OrderBookEntry::stringToOrderBookType(tokens[2]);
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cout << "stringsToOBE Bad Float: " << tokens[3] << std::endl;
        std::cout << "stringsToOBE Bad Float: " << tokens[4] << std::endl;
    }

    OrderBookEntry Obe{price, amount, timestamp, product, orderType};
    return Obe;
};

OrderBookEntry CSVReader::inputToOBE(std::string priceString,
                                     std::string amountString,
                                     std::string timestamp, std::string product,
                                     OrderBookType orderType) {
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cout << "inputToOBE Bad Float: " << price << std::endl;
        std::cout << "inputToOBE Bad Float: " << amount << std::endl;
    }
    OrderBookEntry obe{price, amount, timestamp, product, orderType};
    return obe;
}