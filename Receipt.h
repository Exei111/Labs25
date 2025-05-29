#ifndef RECEIPT_H
#define RECEIPT_H

#include "Document.h"

class Receipt : public Document {
private:
    char date[20];
    char recipient[100];

public:
    Receipt(const char* title, double amount, const char* date, const char* recipient);
    ~Receipt();
    void show() const override;
};

Receipt::Receipt(const char* title, double amount, const char* date, const char* recipient)
    : Document(title, amount) {
    strncpy(this->date, date, sizeof(this->date) - 1);
    this->date[sizeof(this->date) - 1] = '\0';
    strncpy(this->recipient, recipient, sizeof(this->recipient) - 1);
    this->recipient[sizeof(this->recipient) - 1] = '\0';
    std::cout << "Receipt()" << std::endl;
}

Receipt::~Receipt() {
    std::cout << "~Receipt()" << std::endl;
}

void Receipt::show() const {
    std::cout << "Квитанция: " << getTitle() << ", Сумма: " << getAmount()
              << ", Дата: " << date
              << ", Получатель: " << recipient << std::endl;
}

#endif // RECEIPT_H