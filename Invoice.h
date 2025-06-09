#ifndef INVOICE_H
#define INVOICE_H

#include "Document.h"

class Invoice : public Document {
private:
    char invoiceNumber[20];
    char fromCompany[100];
    char toCompany[100];
    char goodsDescription[200];

public:
    Invoice(const char* title, double amount, 
            const char* invoiceNumber, const char* fromCompany, 
            const char* toCompany, const char* goodsDescription);
    void show() const override;
};

Invoice::Invoice(const char* title, double amount, 
                 const char* invoiceNumber, const char* fromCompany,
                 const char* toCompany, const char* goodsDescription)
    : Document(title, amount) {
    strncpy(this->invoiceNumber, invoiceNumber, sizeof(this->invoiceNumber) - 1);
    this->invoiceNumber[sizeof(this->invoiceNumber) - 1] = '\0';
    strncpy(this->fromCompany, fromCompany, sizeof(this->fromCompany) - 1);
    this->fromCompany[sizeof(this->fromCompany) - 1] = '\0';
    strncpy(this->toCompany, toCompany, sizeof(this->toCompany) - 1);
    this->toCompany[sizeof(this->toCompany) - 1] = '\0';
    strncpy(this->goodsDescription, goodsDescription, sizeof(this->goodsDescription) - 1);
    this->goodsDescription[sizeof(this->goodsDescription) - 1] = '\0';
}

void Invoice::show() const {
    std::cout << "НАКЛАДНАЯ\n"
              << "Номер: " << invoiceNumber << "\n"
              << "От: " << fromCompany << "\n"
              << "Кому: " << toCompany << "\n"
              << "Товары: " << goodsDescription << "\n"
              << "Сумма: " << getAmount() << "\n"
              << "----------------------------------------\n";
}

#endif // INVOICE_H