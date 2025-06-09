#include "products.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

namespace store {
    Product::Product(const char* name, double price, double weight, int quantity) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->price = price;
        this->weight = weight;
        this->quantity = quantity;
    }

    Product::Product() {
        this->name = new char[5];
        strcpy(this->name, "name");
        this->price = 0.0;
        this->weight = 0.0;
        this->quantity = 0;
    }

    Product::Product(const Product& other) {
        
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->price = other.price;
        this->weight = other.weight;
        this->quantity = other.quantity;
    }

    Product& Product::operator=(const Product& other) {
        if (this == &other) return *this;

        delete[] name;

        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->price = other.price;
        this->weight = other.weight;
        this->quantity = other.quantity;

        return *this;
    }

    Product::~Product() {
        delete[] name;
    }

    bool Product::operator==(const Product& other) {
        return strcmp(name, other.name) == 0;
    }

    bool Product::operator>(const Product& other) {
        return price > other.price;
    }

    std::ostream& operator<<(std::ostream& out, const Product& other) {
        out << other.name << " " << other.price << " " << other.weight << " " << other.quantity;
        return out;
    }

    std::ifstream& operator>>(std::ifstream& in, Product& other) {
        char tempName[100];
        in >> tempName >> other.price >> other.weight >> other.quantity;
        other.setName(tempName);
        return in;
    }
    
    Product* Product::products = nullptr;
    int Product::size = 1;
    int Product::index = 0;
    
    void Product::loadFromFile(const char* filename) {
        products = new Product[size];
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл" << std::endl;
            return;
        }
        index = 0;
        while (file >> products[index]) {
            index++;
            if (index >= size) {
                size *= 2;
                Product* newProducts = new Product[size];
                std::copy(products, products + index, newProducts);
                delete[] products;
                products = newProducts;
            }
        }
    }

    void Product::sort() {
        for (int i = 0; i < index + 1; i++) {
            bool isSwaped = false;
            for (int j = 0; j < index - i; j++) {
                if (products[j].weight > products[j+1].weight) {
                    std::swap(products[j].weight, products[j+1].weight);
                }
            }
        }
    }
    

    void Product::printDb() {
        for (int i = 0; i < index; i++) {
            std::cout << products[i] << std::endl;
        }
    }

    void Product::addToDb(const char* name, double price, double weight, int quantity) {
        addToDb(Product(name, price, weight, quantity));
    }

    void Product::addToDb(Product newProduct) {
        if (index >= size) {
            size *= 2;
            Product* newProducts = new Product[size];
            std::copy(products, products + index, newProducts);
            delete[] products;
            products = newProducts;
        }
        products[index++] = newProduct;
    }

    void Product::removeFromDb(const char* name) {
        int pos = getIndexOfProduct(name);
        if (pos == -1) return;
        for (int i = pos; i < index - 1; i++) {
            products[i] = products[i + 1];
        }
        index--;
    }

    void Product::saveToFile() {
        std::ofstream out("database2.txt");
        if (!out) {
            std::cout << "Не удалось открыть файл" << std::endl;
            return;
        }
        for (int i = 0; i < index; i++) {
            out << products[i] << "\n";
        }
    }

    void Product::editDb(const char* name, Product newValue) {
        int pos = getIndexOfProduct(name);
        if (pos != -1) {
            products[pos] = newValue;
        }
    }

    int Product::getIndexOfProduct(Product findProduct) {
        return getIndexOfProduct(findProduct.getName());
    }

    int Product::getIndexOfProduct(const char* findName) {
        for (int i = 0; i < index; i++) {
            if (strcmp(products[i].getName(), findName) == 0) {
                return i;
            }
        }
        std::cout << "Продукт не найден: " << findName << std::endl;
        return -1;
    }

    char* Product::getName() {
        return name;
    }

    double Product::getPrice() {
        return price;
    }

    double Product::getWeight() {
        return weight;
    }

    int Product::getQuantity() {
        return quantity;
    }

    void Product::setName(const char* name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void Product::setPrice(double price) {
        this->price = price;
    }

    void Product::setWeight(double weight) {
        this->weight = weight;
    }

    void Product::setQuantity(int quantity) {
        this->quantity = quantity;
    }
}
