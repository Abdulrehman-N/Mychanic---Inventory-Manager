#include <string>
#include <vector>

class Item {
public:
    // Constructor to initialize item properties
    Item(const std::string& name, int quantity, double price)
        : name(name), quantity(quantity), price(price) {}

    // Getter methods to access item properties
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    // Setter methods to update item properties
    void setName(const std::string& newName) { name = newName; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
    
private:
    std::string name;
    int quantity;
    double price;
};