#include "Document.h"
#include "Receipt.h"
#include "Invoice.h"
#include "Check.h"
#include "MyStack.h"
#include <iostream>
#include <limits>

void print(const MyStack<Document*>& stack) {
    if (stack.empty()) {
        std::cout << "Стек пуст.\n";
        return;
    }

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
        std::cout << "Стек пуст.\n";
        return;
    }

    if (index == 1) {
        delete stack.topInf();
        stack.pop();
        std::cout << "Элемент с индексом " << index << " удален.\n";
        return;
    }

    auto* prev = stack.getTopNode();
    for (size_t i = 1; i < index - 1 && prev != nullptr; ++i) {
        prev = MyStack<Document*>::getNextNode(prev);
    }

    if (prev == nullptr || MyStack<Document*>::getNextNode(prev) == nullptr) {
        std::cout << "Индекс " << index << " вне диапазона.\n";
        return;
    }

    auto* toDelete = MyStack<Document*>::getNextNode(prev);
    prev->next = toDelete->next;
    delete toDelete->d;
    delete toDelete;
    std::cout << "Элемент с индексом " << index << " удален.\n";
}

void clear(MyStack<Document*>& stack) {
    while (!stack.empty()) {
        delete stack.topInf(); 
        stack.pop();          
    }
    std::cout << "Стек очищен.\n";
}

void addDocument(MyStack<Document*>& stack) {
    std::cout << "\nВыберите тип документа:\n"
              << "1. Квитанция\n"
              << "2. Накладная\n"
              << "3. Чек\n"
              << "Ваш выбор: ";
    
    int type;
    std::cin >> type;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    char title[100];
    double amount;

    std::cout << "Введите название документа: ";
    std::cin.getline(title, 100);

    std::cout << "Введите сумму: ";
    std::cin >> amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        if (type == 1) {
            char date[20], payer[100], purpose[200];
            std::cout << "Введите дату оплаты (ГГГГ-ММ-ДД): ";
            std::cin.getline(date, 20);
            std::cout << "Введите плательщика: ";
            std::cin.getline(payer, 100);
            std::cout << "Введите цель платежа: ";
            std::cin.getline(purpose, 200);
            stack.push(new Receipt(title, amount, date, payer, purpose));
        }
        else if (type == 2) {
            char number[20], from[100], to[100], goods[200];
            std::cout << "Введите номер накладной: ";
            std::cin.getline(number, 20);
            std::cout << "Введите отправителя: ";
            std::cin.getline(from, 100);
            std::cout << "Введите получателя: ";
            std::cin.getline(to, 100);
            std::cout << "Введите описание товаров: ";
            std::cin.getline(goods, 200);
            stack.push(new Invoice(title, amount, number, from, to, goods));
        }
        else if (type == 3) {
            char number[20], bank[50], account[30], time[20];
            std::cout << "Введите номер чека: ";
            std::cin.getline(number, 20);
            std::cout << "Введите название банка: ";
            std::cin.getline(bank, 50);
            std::cout << "Введите номер счета: ";
            std::cin.getline(account, 30);
            std::cout << "Введите время операции (ЧЧ:ММ:СС): ";
            std::cin.getline(time, 20);
            stack.push(new Check(title, amount, number, bank, account, time));
        }
        else {
            std::cout << "Неверный тип документа.\n";
            return;
        }
        std::cout << "Документ добавлен в стек.\n";
    } catch (...) {
        std::cout << "Ошибка при создании документа.\n";
    }
}

int main() {
    MyStack<Document*> stack;

    stack.push(new Receipt("Оплата за электричество", 2543.75, 
                          "2023-11-20", "Петров А.А.", "За ноябрь 2023"));
    stack.push(new Invoice("Поставка мебели", 120500.00, 
                         "INV-2023-789", "ООО МебельПро", 
                         "ООО ОфисПлюс", "Столы офисные (10 шт.), Кресла (15 шт.)"));
    stack.push(new Check("Оплата услуг химчистки", 3500.00, 
                        "CHK-2023-123", "Альфа-Банк", 
                        "40817810500009876543", "15:45:30"));

    print(stack);

    while (true) {
        std::cout << "\nМеню управления документами:\n"
                  << "1. Добавить документ\n"
                  << "2. Удалить документ по индексу\n"
                  << "3. Просмотреть все документы\n"
                  << "4. Очистить стек\n"
                  << "5. Выход\n"
                  << "Выберите действие: ";
        
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addDocument(stack);
                break;
            case 2: {
                size_t index;
                std::cout << "Введите индекс документа для удаления: ";
                std::cin >> index;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный индекс.\n";
                } else {
                    remove(stack, index);
                }
                break;
            }
            case 3:
                print(stack);
                break;
            case 4:
                clear(stack);
                break;
            case 5:
                clear(stack);
                return 0;
            default:
                std::cout << "Неверный выбор. Пожалуйста, введите число от 1 до 5.\n";
        }
    }
}