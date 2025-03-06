#include "fraction.h"
#include <cstring>
#include <cmath>


Fraction::Fraction() {
    numerator = 0;
    denominator = 1;
}

Fraction::Fraction(const char* str) {
    int whole = 0;
    int num = 0;
    int denom = 0;
    bool negative = false;

    if (std::strlen(str) > 9) {
        throw std::invalid_argument("Перегрузка программы при введении дроби");
    }

    const char* slash = std::strchr(str, '/');
    const char* space = std::strchr(str, ' ');

    if (str[0] == '-') {
        negative = true;
        str++;
    }

    if (space != nullptr) {
        whole = std::atoi(str);
        str = space + 1;
    }

    if (slash != nullptr) {
        num = std::atoi(str);
        denom = std::atoi(slash + 1);
    } else {
        whole = std::atoi(str);
    }

    if (denom == 0) {
        throw std::invalid_argument("Неверна введена дробь.");
    }
    numerator = whole * denom + num;
    if (negative) {
        numerator = -numerator;
    }
    denominator = denom;

    reduce();
}


Fraction::Fraction(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Неверна введена дробь.");
    }

    this->numerator = numerator;
    this->denominator = denominator;
    reduce();
}


Fraction::Fraction(double value, int precision) {

    denominator = 1;
    for (int i = 0; i < precision; ++i) {
        denominator *= 10;
    }
    numerator = static_cast<int>(value * denominator);
    reduce();
}

int greatesCommonDivisor(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Fraction::reduce() {
    int commonDivisor = greatesCommonDivisor(std::abs(numerator), std::abs(denominator));
    numerator /= commonDivisor;
    denominator /= commonDivisor;
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}


std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    if (frac.denominator == 1) {
        out << frac.numerator;
    } else if (std::abs(frac.numerator) > frac.denominator) {
        int whole = frac.numerator / frac.denominator;
        int remNum = std::abs(frac.numerator) % frac.denominator;
        out << whole << " " << remNum << "/" << frac.denominator;
    } else {
        out << frac.numerator << "/" << frac.denominator;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& frac) {
    char buffer[100];
    in.getline(buffer, 100);
    frac = Fraction(buffer);
    return in;
}

Fraction Fraction::operator+(const Fraction& other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int denom = denominator * other.denominator;
    Fraction result(num, denom);
    result.reduce();
    return result;
}

Fraction Fraction::operator+(int value) const {
    return *this + Fraction(value);
}

Fraction Fraction::operator+(double value) const {
    return *this + Fraction(value);
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator+=(int value) {
    *this = *this + value;
    return *this;
}

Fraction& Fraction::operator+=(double value) {
    *this = *this + value;
    return *this;
}

Fraction operator+(int value, const Fraction& frac) {
    return frac + value;
}

Fraction operator+(double value, const Fraction& frac) {
    return frac + value;
}