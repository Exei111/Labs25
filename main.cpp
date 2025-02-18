#include <iostream>
#include "mymath/mymath.h"
#include "mymathnew/mymathnew.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Я умею суммировать! Зацени 10+32=";
    std::cout << mymath::sum(10, 32) << std::endl;

    std::cout << "А также умножать: ";
    std::cout << "10 * 32 = ";
    std::cout << mymathnew::multiply(10, 32) << std::endl;
    std::cout << "И делить 32/10 = ";
    std::cout << mymathnew::divide(32, 10) << std::endl;
    


    return 0;
}