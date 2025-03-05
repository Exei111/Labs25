#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

namespace store {
    
enum class MenuOption {
    PrintDb = 1,
    AddProduct,
    RemoveProduct,
    EditProduct,
    SortDb,
    Exit
};


class Product {
public:
    Product(const char* name, double price, double weight, int quantity);
    Product();
    Product(const Product& other);
    ~Product();

    Product& operator=(const Product& other);
    bool operator==(const Product& other);
    bool operator>(const Product& other);
    
    friend std::ostream& operator<<(std::ostream& out, const Product& other);
    friend std::ifstream& operator>>(std::ifstream& in, Product& other);

    static void loadFromFile(const char* filename);
    static void sort();
    static void printDb();
    static void addToDb(const char* name, double price, double weight, int quantity);
    static void addToDb(Product newProduct);
    static void removeFromDb(const char* name);
    static void saveToFile();
    static void editDb(const char* name, Product newValue);

    static int getIndexOfProduct(Product findProduct);
    static int getIndexOfProduct(const char* findName);

    char* getName();
    double getPrice();
    double getWeight();
    int getQuantity();

    void setName(const char* name);
    void setPrice(double price);
    void setWeight(double weight);
    void setQuantity(int quantity);

private:
    char* name;
    double price;
    double weight;
    int quantity;
    
    static int size;
    static int index;
    static Product* products;
};

} // namespace store

#endif // PRODUCT_H
