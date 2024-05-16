#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "MychanicClasses.h" // Assuming this includes the Item class definition

// Function to convert a string to uppercase
std::string toUpper(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::toupper(c);
    }
    return result;
}

std::vector<Item> inventory;
double profits=0.0;
double balance=5000.0;

void processInventory() {
    int counter=1;
    std::cout << "Inventory Listing:\n" << std::endl;
    for (const Item& item : inventory) {
        std::cout << "Product Number: " << counter << std::endl;
        std::cout << "----------------------" << std::endl;
        std::cout << "Item Name: " << item.getName() << std::endl;
        std::cout << "Quantity: " << item.getQuantity() << std::endl;
        std::cout << "Price: $" << item.getPrice() << std::endl;
        std::cout << "----------------------" << std::endl;
        counter++;
    }
}

void loadInv(std::string fname) {
    
    std::ifstream inFile(fname);

    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::string name, quantityStr, priceStr;
        int quantity;
        double price;

        std::istringstream sstream(line);

        // Read each field using semicolon as a delimiter
        std::getline(sstream, name, ';');
        std::getline(sstream, quantityStr, ';');
        std::getline(sstream, priceStr, ';');

        // Convert quantity and price from string to appropriate types
        try {
            quantity = std::stoi(quantityStr);
            price = std::stod(priceStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid format in line: " << line << std::endl;
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Value out of range in line: " << line << std::endl;
            continue;
        }

        // Push the item into the inventory
        inventory.push_back(Item(name, quantity, price));
    }

    inFile.close();
}
Item* itemExists(const std::string& name) {
    for (Item& item : inventory) {
        if (toUpper(item.getName()) == toUpper(name)) {
            return &item; // Return pointer to the found item
        }
    }
    return nullptr; // Item not found, return nullptr
}

void sellItem(Item& product, int& amount) {
    if (product.getQuantity()-amount >= 0) {
        product.setQuantity(product.getQuantity() - amount);
        std::cout << "Sold "<< amount <<" unit of " << product.getName() << "." << std::endl;
        profits+=product.getPrice()*amount;
    } else {
        std::cout << "No more units of " << product.getName() << " available for sale." << std::endl;
    }
}

void stockItem(Item& product, int& amount){
    if (amount > 0 && balance-((product.getPrice()/2.0)*amount)>=0) {
        product.setQuantity(product.getQuantity() + amount);
        std::cout << "Stocked "<< amount <<" unit of " << product.getName() << "." << std::endl;
        balance-=(product.getPrice()/2.0)*amount;
    } else {
        std::cout << "Invalid Amount!" << std::endl;
    }
}

void addProduct(std::string name, int quantity, double price){
    inventory.push_back(Item(name, quantity, price));
}



void removeProduct(int number){
    if(inventory.size()>=number){
        inventory.erase(inventory.begin()+number);
    }
    else{
        std::cout<<"Invlaid Product Number!"<<std::endl;
    }
}

int main() {
    std::cout << "Welcome to Mychanic - Inventory Manager\n";
    std::cout << "Please select one of the following options:" << std::endl;
    std::cout << "1.) VIEWINV - View Inventory" << std::endl;
    std::cout << "2.) LDINV - Load Inventory from a file" << std::endl;
    std::cout << "3.) SELL - Sell Item" << std::endl;
    std::cout << "4.) STK - Stock up an Item" << std::endl;
    std::cout << "5.) WLT - View current balance and profits" << std::endl;
    std::cout << "6.) ADD- Add a product" << std::endl;
    std::cout << "7.) RMV - Remove a product" << std::endl;
    std::cout << "8.) Q - Quit" << std::endl;

    bool mloop = true;
    std::string command;
    while (mloop) {
        std::cout << "\n>";
        std::getline(std::cin, command); // Read entire line of input

        if (toUpper(command) == "Q") {
            mloop = false;
        } else if (toUpper(command) == "VIEWINV") {
            processInventory();
        } else if (toUpper(command) == "LDINV") {
            std::string fname;
            std::cout << "Enter the file name: ";
            std::getline(std::cin, fname); // Read item name to sell
            loadInv(fname);
        } else if (toUpper(command) == "SELL") {
            std::string sellp;
            std::cout << "Enter item name to sell: ";
            std::getline(std::cin, sellp); // Read item name to sell
            Item* itemToSell = itemExists(sellp);
            std::cout<<"Amount: ";
            int amount1;
            std::cin>>amount1;
            if (itemToSell != nullptr) {
                sellItem(*itemToSell,amount1); // Sell the found item
            } else {
                std::cout << "Item not found in inventory." << std::endl;
            }
        }
        else if (toUpper(command) == "WLT") {
            std::cout<<"Current balance: $"<<balance<<std::endl;
            std::cout<<"Profits: $"<<profits<<std::endl;
        }
        else if (toUpper(command) == "ADD") {
            std::string name1;
            std::cout<<"Product name: "<<std::endl;
            std::getline(std::cin, name1);
            std::cout<<"Qauntity: "<<std::endl;
            int quantity1;
            std::cin>>quantity1;
            std::cout<<"Price: $"<<std::endl;
            double price1;
            std::cin>>price1;
            addProduct(name1,quantity1,price1);
        }
        else if (toUpper(command) == "RMV") {
            std::cout<<"Enter the product number: "<<std::endl;
            int tormv;
            std::cin>>tormv;
            removeProduct(tormv-1);
        }
        else if (toUpper(command) == "STK") {
            std::string stockp;
            std::cout << "Enter item name to stock-up: ";
            std::getline(std::cin, stockp); // Read item name to sell
            Item* itemToSell = itemExists(stockp);
            std::cout<<"Amount: ";
            int amount1;
            std::cin>>amount1;
            if (itemToSell != nullptr) {
                stockItem(*itemToSell,amount1); // Sell the found item
            } else {
                std::cout << "Item not found in inventory." << std::endl;
            }
        }
    }

    return 0;
}
