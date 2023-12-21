#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "OrderBookEntry.h"

class CSVReader {
   public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenise(std::string line, char separator);
    static OrderBookEntry inputToOBE(std::string price, std::string amount,
                                     std::string timestamp, std::string product,
                                     OrderBookType orderType);

   private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};
