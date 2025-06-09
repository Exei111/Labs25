#ifndef RECEIPT_H
#define RECEIPT_H

#include "Document.h"

class Receipt : public Document {
private:
    char paymentDate[20];
    char payer[100];
    char paymentPurpose[200];

public:
    Receipt(const char* title, double amount, 
            const char* paymentDate, const char* payer, const char* paymentPurpose);
    void show() const override;
};

Receipt::Receipt(const char* title, double amount, 
                 const char* paymentDate, const char* payer, const char* paymentPurpose)
    : Document(title, amount) {
    strncpy(this->paymentDate, paymentDate, sizeof(this->paymentDate) - 1);
    this->paymentDate[sizeof(this->paymentDate) - 1] = '\0';
    strncpy(this->payer, payer, sizeof(this->payer) - 1);
    this->payer[sizeof(this->payer) - 1] = '\0';
    strncpy(this->paymentPurpose, paymentPurpose, sizeof(this->paymentPurpose) - 1);
    this->paymentPurpose[sizeof(this->paymentPurpose) - 1] = '\0';
}

void Receipt::show() const {
    std::cout << "КВИТАНЦИЯ\n"
              << "Название: " << getTitle() << "\n"
              << "Сумма: " << getAmount() << "\n"
              << "Дата оплаты: " << paymentDate << "\n"
              << "Плательщик: " << payer << "\n"
              << "Цель платежа: " << paymentPurpose << "\n"
              << "----------------------------------------\n";
}

#endif // RECEIPT_H