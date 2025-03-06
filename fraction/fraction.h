#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

    void reduce();

public:
    Fraction();
    Fraction(const char* str);
    Fraction(int num, int denom = 1);
    Fraction(double value, int precision = 4);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
    friend std::istream& operator>>(std::istream& in, Fraction& frac);

    Fraction operator+(const Fraction& other) const;
    Fraction operator+(int value) const;
    Fraction operator+(double value) const;
    Fraction& operator+=(const Fraction& other);
    Fraction& operator+=(int value);
    Fraction& operator+=(double value);

    friend Fraction operator+(int value, const Fraction& frac);
    friend Fraction operator+(double value, const Fraction& frac);
};

#endif // FRACTION_H