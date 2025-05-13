#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <cstring>

class Term {
private:
    int coefficient; 
    int exponent;    

public:
   
    Term() : coefficient(0), exponent(0) {}
    Term(int coeff) : coefficient(coeff), exponent(0) {}
    Term(int coeff, int exp) : coefficient(coeff), exponent(exp) {}

    Term operator+(const Term& other) const;
    Term operator-(const Term& other) const;
    Term operator*(const Term& other) const;

    friend std::istream& operator>>(std::istream& is, Term& term);
    friend std::ostream& operator<<(std::ostream& os, const Term& term);

    int getCoefficient() const { return coefficient; }
    int getExponent() const { return exponent; }

    friend class Polynomial;
};

Term Term::operator+(const Term& other) const {
    if (exponent != other.exponent) {
        throw std::invalid_argument("error");
    }
    return Term(coefficient + other.coefficient, exponent);
}

Term Term::operator-(const Term& other) const {
    if (exponent != other.exponent) {
        throw std::invalid_argument("Cannot subtract terms with different exponents.");
    }
    return Term(coefficient - other.coefficient, exponent);
}

Term Term::operator*(const Term& other) const {
    return Term(coefficient * other.coefficient, exponent + other.exponent);
}

std::istream& operator>>(std::istream& is, Term& term) {
    char buffer[256];
    is >> buffer;

    const char* x_pos = strstr(buffer, "x");
    if (!x_pos) {
        term.coefficient = atoi(buffer);
        term.exponent = 0;
    } else {
        term.coefficient = (x_pos == buffer) ? 1 : atoi(buffer);
        const char* caret_pos = strchr(buffer, '^');
        term.exponent = caret_pos ? atoi(caret_pos + 1) : 1;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.coefficient == 0) {
        os << "0";
    } else {
        if (term.coefficient != 1 || term.exponent == 0) {
            os << term.coefficient;
        }
        if (term.exponent > 0) {
            os << "x";
            if (term.exponent > 1) {
                os << "^" << term.exponent;
            }
        }
    }
    return os;
}

#endif // TERM_H