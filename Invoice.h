#ifndef INVOICE_H
#define INVOICE_H

#include "Document.h"

class Invoice : public Document {
private:
    char number[50];
    char sender[100];

public:
    Invoice(const char* title, double amount, const char* number, const char* sender);
    ~Invoice();
    void show() const override;
};

Invoice::Invoice(const char* title, double amount, const char* number, const char* sender)
    : Document(title, amount) {
    strncpy(this->number, number, sizeof(this->number) - 1);
    this->number[sizeof(this->number) - 1] = '\0';
    strncpy(this->sender, sender, sizeof(this->sender) - 1);
    this->sender[sizeof(this->sender) - 1] = '\0';
    std::cout << "Invoice()" << std::endl;
}

Invoice::~Invoice() {
    std::cout << "~Invoice()" << std::endl;
}

void Invoice::show() const {
    std::cout << "Накладная: " << getTitle() << ", Сумма: " << getAmount()
              << ", Номер: " << number
              << ", Отправитель: " << sender << std::endl;
}

#endif // INVOICE_H