#include "Document.h"
#include "Receipt.h"
#include "Invoice.h"
#include "Check.h"
#include "MyStack.h"
#include <iostream>

void print(const MyStack<Document*>& stack) {
    auto* current = stack.getTopNode();
    size_t index = 0;
    while (current != nullptr) {
        std::cout << ++index << ": ";
        current->d->show();
        current = MyStack<Document*>::getNextNode(current);
    }
}

void remove(MyStack<Document*>& stack, size_t index) {
    if (stack.empty()) {
        std::cout << "Стек пуст" << std::endl;
        return;
    }

    if (index == 1) {
        delete stack.topInf();
        stack.pop();
        std::cout << "Элемент с индексом " << index << " удален." << std::endl;
        return;
    }

    auto* prev = stack.getTopNode();
    for (size_t i = 1; i < index - 1 && prev != nullptr; ++i) {
        prev = MyStack<Document*>::getNextNode(prev);
    }

    if (prev == nullptr || MyStack<Document*>::getNextNode(prev) == nullptr) {
        std::cout << "Индекс " << index << " вне диапазона." << std::endl;
        return;
    }

    auto* toDelete = MyStack<Document*>::getNextNode(prev);
    prev->next = toDelete->next;
    delete toDelete->d;
    delete toDelete;
    std::cout << "Элемент с индексом " << index << " удален." << std::endl;
}

void clear(MyStack<Document*>& stack) {
    while (!stack.empty()) {
        delete stack.topInf(); 
        stack.pop();          
    }
    std::cout << "Стек очищен." << std::endl;
}

int main() {
    MyStack<Document*> stack;

    stack.push(new Receipt("За коммунальные услуги", 2500.50, "2023-10-15", "Иванов И.И."));
    stack.push(new Invoice("Поставка товаров", 15000.75, "INV-2023-456", "ООО Поставщик"));
    stack.push(new Check("Оплата услуг", 5000.00, "CHK-987654", "Сбербанк"));

    print(stack);

    while (true) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить\n"
                  << "2. Удалить по индексу\n"
                  << "3. Показать\n"
                  << "4. Очистить стек\n"
                  << "5. Выйти\n"
                  << "Выберите действие: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Введите тип документа (1 - Квитанция, 2 - Накладная, 3 - Чек): ";
            int type;
            std::cin >> type;
            if (type == 1) {
                char title[100], date[20], recipient[100];
                double amount;
                std::cout << "Введите название, сумму, дату и получателя: ";
                std::cin.ignore();
                std::cin.getline(title, 100);
                std::cin >> amount >> date >> recipient;
                stack.push(new Receipt(title, amount, date, recipient));
            } else if (type == 2) {
                char title[100], number[50], sender[100];
                double amount;
                std::cout << "Введите название, сумму, номер и отправителя: ";
                std::cin.ignore();
                std::cin.getline(title, 100);
                std::cin >> amount >> number >> sender;
                stack.push(new Invoice(title, amount, number, sender));
            } else if (type == 3) {
                char title[100], checkNumber[20], bankName[50];
                double amount;
                std::cout << "Введите название, сумму, номер чека и банк: ";
                std::cin.ignore();
                std::cin.getline(title, 100);
                std::cin >> amount >> checkNumber >> bankName;
                stack.push(new Check(title, amount, checkNumber, bankName));
            }
        } else if (choice == 2) {
            std::cout << "Введите номер элемента для удаления: ";
            size_t index;
            std::cin >> index;
            remove(stack, index); 
        } else if (choice == 3) {
            print(stack);
        } else if (choice == 4) {
            clear(stack);
        } else if (choice == 5) {
            break;
        }
    }

    clear(stack); 
    return 0;
}