#include "planets/planets.h"
#include "products/products.h"
#include <iostream>
#include <fstream>

int main() {
    planets::Planet::loadFromFile("database.txt");
    planets::Planet::removeFromDb("Planet1");

    planets::Planet::printDb();
    std::cout << "\n";

    planets::Planet::addToDb("Planet1", 2000, 2, 560);
    planets::Planet newPlanetObj("Planet2", 1500, 3, 400);
    planets::Planet::addToDb(newPlanetObj);

    planets::Planet::printDb();
    std::cout << "\n";

    planets::Planet::sort();

    planets::Planet::printDb();
    std::cout << "\n";

    planets::Planet::removeFromDb("Planet2");
    planets::Planet::printDb();
    planets::Planet::saveToFile();

   
    
    

    std::cout << "--------------------" << std::endl;

    store::Product::loadFromFile("database2.txt");
    
    int choice;
    do {
        std::cout << "\nМеню:\n"
                  << "1) Вывести базу данных продуктов\n"
                  << "2) Добавить продукт в базу данных\n"
                  << "3) Удалить продукт из базы данных\n"
                  << "4) Редактировать продукт\n"
                  << "5) Сортировать базу данных продуктов\n"
                  << "6) Завершить работу\n"
                  << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (static_cast<store::MenuOption>(choice)) {
            case store::MenuOption::PrintDb:
                store::Product::printDb();
                break;
            case store::MenuOption::AddProduct: {
                char name[100];
                double price, weight;
                int quantity;
                std::cout << "Введите название, цену, вес и количество: ";
                std::cin >> name >> price >> weight >> quantity;
                store::Product::addToDb(name, price, weight, quantity);
                break;
            }
            case store::MenuOption::RemoveProduct: {
                char name[100];
                std::cout << "Введите название продукта для удаления: ";
                std::cin >> name;
                store::Product::removeFromDb(name);
                break;
            }
            case store::MenuOption::EditProduct: {
                char name[100];
                char newName[100];
                double price, weight;
                int quantity;
                std::cout << "Введите название продукта, новое название, цену, вес и количество: ";
                std::cin >> name >> newName >> price >> weight >> quantity;
                store::Product newProduct(newName, price, weight, quantity);
                store::Product::editDb(name, newProduct);
                break;
            }
            case store::MenuOption::SortDb:
                store::Product::sort();
                break;
            case store::MenuOption::Exit:
                store::Product::saveToFile();
                
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
                break;
        }
    } while (choice != static_cast<int>(store::MenuOption::Exit));
    
    return 0;
    
}
