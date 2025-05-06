#include <iostream>
#include "MyStack.h"

void multipliers(int n, MyStack<int>& stack) {
    int divisor = 2;
    while (n > 1) {
        while (n % divisor == 0) {
            stack.push(divisor);
            n /= divisor;
        }
        divisor++;
    }
}

int main() {
    int number = 78;
    MyStack<int> stack;

    multipliers(number, stack);

    std::cout << number << " = ";
    MyStack<int> tempStack;

    // Вывод по убыванию
    while (!stack.empty()) {
        int factor = stack.topInf();
        std::cout << factor;
        tempStack.push(factor);
        stack.pop();
        if (!stack.empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;

    // Вывод по возрастанию
    std::cout << number << " = ";
    while (!tempStack.empty()) {
        int factor = tempStack.topInf();
        std::cout << factor;
        tempStack.pop();
        if (!tempStack.empty()) {
            std::cout << " * ";
        }
    }

    MyStack<char> charStack;

    charStack.push('a');
    charStack.push('b');
    charStack.push('c');

    MyStack<char> charStack2 = charStack;
    MyStack<char> charStack3;
    charStack3 = charStack2;

    std::cout << std::endl;

    std::cout << charStack << std::endl;

    std::cout << charStack2 << std::endl;

    std::cout << charStack3 << std::endl;

    std::cout << std::endl;

    return 0;
}