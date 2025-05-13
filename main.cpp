#include <iostream>
#include "lib/Term.h"
#include "lib/Polynomial.h"

int main() {
    Polynomial p1, p2;
    std::cout << "Первый полиномиал: ";
    std::cin >> p1;
    std::cout << "Второй полиномиал: ";
    std::cin >> p2;

    std::cout << "\nВведенные полиномиалы:\n";
    std::cout << "P1: " << p1 << "\n";
    std::cout << "P2: " << p2 << "\n";

    Polynomial sum = p1 + p2;
    Polynomial dif = p1 - p2;
    Polynomial product = p1 * p2;

    std::cout << "\nСумма: " << sum << "\n";
    std::cout << "Разность:" << dif << "\n";
    std::cout << "Умножение: " << product << "\n";

    return 0;
}