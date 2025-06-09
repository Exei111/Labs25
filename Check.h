#ifndef CHECK_H
#define CHECK_H

#include "Document.h"

class Check : public Document {
private:
    char checkNumber[20];
    char bankName[50];
    char accountNumber[30];
    char transactionTime[20];

public:
    Check(const char* title, double amount, 
          const char* checkNumber, const char* bankName,
          const char* accountNumber, const char* transactionTime);
    void show() const override;
};

Check::Check(const char* title, double amount, 
             const char* checkNumber, const char* bankName,
             const char* accountNumber, const char* transactionTime)
    : Document(title, amount) {
    strncpy(this->checkNumber, checkNumber, sizeof(this->checkNumber) - 1);
    this->checkNumber[sizeof(this->checkNumber) - 1] = '\0';
    strncpy(this->bankName, bankName, sizeof(this->bankName) - 1);
    this->bankName[sizeof(this->bankName) - 1] = '\0';
    strncpy(this->accountNumber, accountNumber, sizeof(this->accountNumber) - 1);
    this->accountNumber[sizeof(this->accountNumber) - 1] = '\0';
    strncpy(this->transactionTime, transactionTime, sizeof(this->transactionTime) - 1);
    this->transactionTime[sizeof(this->transactionTime) - 1] = '\0';
}

void Check::show() const {
    std::cout << "ЧЕК\n"
              << "Номер чека: " << checkNumber << "\n"
              << "Банк: " << bankName << "\n"
              << "Счет: " << accountNumber << "\n"
              << "Время операции: " << transactionTime << "\n"
              << "Сумма: " << getAmount() << "\n"
              << "Описание: " << getTitle() << "\n"
              << "----------------------------------------\n";
}

#endif // CHECK_H