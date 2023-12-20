
#include "MerkelMain.h"

#include <iostream>
#include <vector>

#include "CSVReader.h"

void MerkelMain::init() {
    loadOrderBook();

    int input;

    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook() {
    orders = CSVReader::readCSV("csvdataset.csv");
}

void MerkelMain::printMenu() {
    std::cout << "1: Print help " << std::endl;
    std::cout << "2: Print Exchange Stats " << std::endl;
    std::cout << "3: Make an Offer " << std::endl;
    std::cout << "4: Make a Bid " << std::endl;
    std::cout << "5: Print Wallet " << std::endl;
    std::cout << "6: Continue " << std::endl;
}

void MerkelMain::printHelp() {
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void MerkelMain::printMarketStats() {
    std::cout << "Total entries in Market: " << orders.size() << " entries"
              << std::endl;
}
void MerkelMain::enterOffer() {
    std::cout << "You're making an offer now." << std::endl;
}
void MerkelMain::enterBid() {
    std::cout << "You're making a bid now." << std::endl;
}
void MerkelMain::printWallet() { std::cout << "Wallet is empty!" << std::endl; }

void MerkelMain::gotoNextTimeframe() {
    std::cout << "Going to next frame!." << std::endl;
}

void MerkelMain::processUserOption(int userOption) {
    if (userOption == 1) {
        printHelp();
    }
    if (userOption == 2) {
        printMarketStats();
    }
    if (userOption == 3) {
        enterOffer();
    }
    if (userOption == 4) {
        enterBid();
    }
    if (userOption == 5) {
        printWallet();
    }
    if (userOption == 6) {
        gotoNextTimeframe();
    } else {
        std::cout << "Invalid choice. Choose 1 - 6\n";
    }
}

int MerkelMain::getUserOption() {
    int userOption;
    std::cout << "Please enter a number from 1 to 6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose " << userOption << " ." << std::endl;
    return userOption;
}