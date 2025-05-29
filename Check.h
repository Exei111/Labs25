#ifndef CHECK_H
#define CHECK_H

#include "Document.h"

class Check : public Document {
private:
    char checkNumber[20];
    char bankName[50];

public:
    Check(const char* title, double amount, const char* checkNumber, const char* bankName);
    ~Check();
    void show() const override;
};

Check::Check(const char* title, double amount, const char* checkNumber, const char* bankName)
    : Document(title, amount) {
    strncpy(this->checkNumber, checkNumber, sizeof(this->checkNumber) - 1);
    this->checkNumber[sizeof(this->checkNumber) - 1] = '\0';
    strncpy(this->bankName, bankName, sizeof(this->bankName) - 1);
    this->bankName[sizeof(this->bankName) - 1] = '\0';
    std::cout << "Check()" << std::endl;
}

Check::~Check() {
    std::cout << "~Check()" << std::endl;
}

void Check::show() const {
    std::cout << "Чек: " << getTitle() << ", Сумма: " << getAmount()
              << ", Номер чека: " << checkNumber
              << ", Банк: " << bankName << std::endl;
}

#endif // CHECK_H