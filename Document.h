#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <cstring>

class Document {
protected:
    char* title;
    double amount;

public:
    Document(const char* title, double amount);
    virtual ~Document();
    virtual void show() const = 0;
    const char* getTitle() const;
    double getAmount() const;
};

Document::Document(const char* title, double amount) : amount(amount) {
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
}

Document::~Document() {
    delete[] title;
}

const char* Document::getTitle() const {
    return title;
}

double Document::getAmount() const {
    return amount;
}

#endif // DOCUMENT_H