#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Term.h"
#include "MyVector.h"
#include <iostream>
#include <cstring>

class Polynomial {
private:
    MyVector<Term> terms; 
    int degree;           

public:
    Polynomial() : degree(0) {}
    Polynomial(int constant) : degree(0) { terms.add_element(Term(constant)); }
    Polynomial(const Term& term) : degree(term.getExponent()) { terms.add_element(term); }
    Polynomial(const Polynomial& other) : terms(other.terms), degree(other.degree) {}

    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

    void simplify(); 
};

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        terms = other.terms;
        degree = other.degree;
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (size_t i = 0; i < other.terms.getSize(); ++i) {
        terms.add_element(other.terms[i]);
    }
    simplify();
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    for (size_t i = 0; i < other.terms.getSize(); ++i) {
        terms.add_element(Term(-other.terms[i].getCoefficient(), other.terms[i].getExponent()));
    }
    simplify();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    MyVector<Term> result;
    for (size_t i = 0; i < terms.getSize(); ++i) {
        for (size_t j = 0; j < other.terms.getSize(); ++j) {
            result.add_element(Term(terms[i].getCoefficient() * other.terms[j].getCoefficient(),
                                    terms[i].getExponent() + other.terms[j].getExponent()));
        }
    }
    terms = result;
    simplify();
    return *this;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    char buffer[1024];
    is.getline(buffer, sizeof(buffer));

    size_t pos = 0;
    size_t len = strlen(buffer);
    while (pos < len) {
        while (pos < len && buffer[pos] == ' ') {
            ++pos;
        }

        int sign = 1;
        if (buffer[pos] == '+' || buffer[pos] == '-') {
            sign = (buffer[pos] == '+') ? 1 : -1;
            ++pos;
        }

        while (pos < len && buffer[pos] == ' ') {
            ++pos;
        }

        size_t end = pos;
        while (end < len && buffer[end] != '+' && buffer[end] != '-') {
            ++end;
        }

        char term_str[256];
        strncpy(term_str, buffer + pos, end - pos);
        term_str[end - pos] = '\0';
        
        Term term;
        const char* x_pos = strstr(term_str, "x");
        if (!x_pos) {
            term = Term(std::atoi(term_str) * sign);
        } else {
            int coeff = (x_pos == term_str) ? 1 : std::atoi(term_str);
            const char* caret_pos = strchr(term_str, '^');
            int exp = caret_pos ? std::atoi(caret_pos + 1) : 1;
            term = Term(coeff * sign, exp);
        }

        poly.terms.add_element(term);
        pos = end;
    }

    poly.simplify();
    return is;
}

void Polynomial::simplify() {
    MyVector<Term> simplified;

    for (size_t i = 0; i < terms.getSize(); ++i) {
        bool merged = false;
        for (size_t j = 0; j < simplified.getSize(); ++j) {
            if (simplified[j].getExponent() == terms[i].getExponent()) {
                simplified[j] = simplified[j] + terms[i];
                merged = true;
                break;
            }
        }
        if (!merged) {
            simplified.add_element(terms[i]);
        }
    }

    for (size_t i = 0; i < simplified.getSize(); ++i) {
        for (size_t j = i + 1; j < simplified.getSize(); ++j) {
            if (simplified[i].getExponent() < simplified[j].getExponent()) {
                std::swap(simplified[i], simplified[j]);
            }
        }
    }

    MyVector<Term> final_terms;
    for (size_t i = 0; i < simplified.getSize(); ++i) {
        if (simplified[i].getCoefficient() != 0) {
            final_terms.add_element(simplified[i]);
        }
    }

    terms = final_terms;
    degree = terms.getSize() == 0 ? 0 : terms[0].getExponent();
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.terms.getSize() == 0) {
        os << "0";
        return os;
    }

    for (size_t i = 0; i < poly.terms.getSize(); ++i) {
        const Term& term = poly.terms[i];

        if (i > 0) {
            if (term.getCoefficient() > 0) {
                os << " + ";
            } else {
                os << " - ";
            }
        } else {
            if (term.getCoefficient() < 0) {
                os << "-";
            }
        }

        int abs_coeff = std::abs(term.getCoefficient());
        if (abs_coeff != 1 || term.getExponent() == 0) {
            os << abs_coeff;
        }

        if (term.getExponent() > 0) {
            os << "x";
            if (term.getExponent() > 1) {
                os << "^" << term.getExponent();
            }
        }
    }

    return os;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result += p2;
    return result;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result -= p2;
    return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result *= p2;
    return result;
}

#endif // POLYNOMIAL_H