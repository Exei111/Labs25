#include "mymathnew.h"
#include <iostream>

namespace mymathnew {
    
    int multiply(int a, int b) {
        return a * b;
    }


    double divide(int a, int b) {
        if (b == 0) {
            std::cout << "Деление на 0 невозможно";
            return 1;
        }
        return static_cast<double>(a) / b;
    }
}
