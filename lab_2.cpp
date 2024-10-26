#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kFieldWidth = 11;
const int kFieldWidthForN = 6;

const int kFive = 5;
const double kStep = 0.2;

const int kSequenceLimitIfAMoreEqualThanZero = 8;
const int kSequenceLimitIfALessEqualThanZero = 9;

const double kEpsilone = 1e-6;
const int kPrecision = 6;

const double kYForThreeSummands = 3;
const double kYForFiveSummands = 5;
const double kYForTenSummands = 10;
}  // namespace

void Task1() {
    std::cout << std::endl
              << "Задача 1 - Сумма натуральных чисел на отрезке от 1 до n, которые делятся на 5 и не делятся на m (m < n)\n"
              << std::endl;
    int m = 0;
    int n = 0;
    int sum = 0;
    std::cout << "Введите n и затеим m (m<n): ";
    std::cin >> n >> m;

    if (m >= n) {
        std::cout << "Ошибка, m не может быть больше или равен n\n";
        return;
    } else if (m == 0) {
        std::cout << "Ошибка, m не может быть равен 0\n";
        return;
    }

    for (int i = 0; i <= n; i += kFive) {
        if (i % m != 0) {
            sum += i;
        }
    }

    std::cout << sum << std::endl;
}

void Task2() {
    std::cout << std::endl << "Задача 2 - вычисление произведения(П)\n" << std::endl;
    double product = 1;
    double a = 0;
    std::cout << "Введите число а: ";
    std::cin >> a;

    if (a >= 0) {
        for (int i = 2; i <= kSequenceLimitIfAMoreEqualThanZero; i += 2) {
            product *= i * i;
        }
        product -= a;
    } else {
        for (int i = 3; i <= kSequenceLimitIfALessEqualThanZero; i += 3) {
            product *= i - 2;
        }
    }
    std::cout << std::setw(kFieldWidthForN) << std::right << std::fixed << std::setprecision(kPrecision) << product << std::endl;
}

void Task3() {
    std::cout << std::endl
              << "Задача 3 - вычисление функции Y = (1- x ^ 2 / 2) * cos(x) - x / 2 * sin(x) и функции вычисляющей этот Y (S)\n"
              << std::endl;
    double summand = 1;
    double S = 0;
    double Y = 0;
    double x = 0;
    std::cout << std::setw(kFieldWidth) << std::right << std::fixed << std::setprecision(kPrecision) << "x";
    std::cout << std::setw(kFieldWidth) << std::right << std::fixed << std::setprecision(kPrecision) << "Y";
    std::cout << std::setw(kFieldWidth) << std::right << std::fixed << std::setprecision(kPrecision) << "S";
    std::cout << std::setw(kFieldWidthForN) << std::right << std::fixed << "N" << std::endl;

    while (x <= 1.) {
        int n = 1;
        summand = 1;
        while (std::abs(summand) >= kEpsilone) {
            S += summand;
            summand *= -(2 * n * n + 1) * x * x / ((2 * n * n - 4 * n + 3) * (2 * n - 1) * n * 2);
            ;
            ++n;
        }

        Y = (1 - x * x / 2) * std::cos(x) - x / 2 * std::sin(x);
        std::cout << std::setw(kFieldWidth) << std::right << std::fixed << std::setprecision(kPrecision) << x;
        std::cout << std::setw(kFieldWidth) << std::right << std::fixed << std::setprecision(kPrecision) << Y;
        std::cout << std::setw(kFieldWidth) << std::right << std::fixed << std::setprecision(kPrecision) << S;
        std::cout << std::setw(kFieldWidthForN) << std::right << std::fixed << n << std::endl;
        S = 0;
        x += kStep;
    }
}

void Task4() {
    std::cout << std::endl << "Задача 4 - вычисление y по формуле\n" << std::endl;

    int N = 0;

    std::cout << "Введите натуральное число n: ";
    std::cin >> N;

    if (N <= 0) {
        std::cout << "Ошибка, n не может быть меньше единицы\n";
        return;
    }

    double y = 0.0;

    for (int i = 1; i <= N; ++i) {
        y = sqrt(2 * i + y);
        if (i == kYForThreeSummands || i == kYForFiveSummands || i == kYForTenSummands) {
            std::cout << "y при " << i << " слагаемых = " << std::setw(kFieldWidth) << std::left << std::fixed << std::setprecision(kPrecision) << y
                      << std::endl;
        }
    }

    if (N == kYForThreeSummands || N == kYForFiveSummands || N == kYForTenSummands) {
        std::cout << "это итоговый y" << std::endl;
    } else {
        std::cout << "итоговый y = " << y << std::endl;
    }
}

int main(int, char**) {
    int taskOfNumber = 0;
    char userChoice = 'y';
    while (userChoice == 'y') {
        std::cout << "Допустимые команды:\n"
                  << "1 - 1 задача\n"
                  << "2 - 2 задача\n"
                  << "3 - 3 задача\n"
                  << "4 - 4 задача\n"
                  << "0 - завершение\n"
                  << "Введите номер задачи:\n";
        std::cin >> taskOfNumber;

        switch (taskOfNumber) {
            case 1:
                Task1();
                break;
            case 2:
                Task2();
                break;
            case 3:
                Task3();
                break;
            case 4:
                Task4();
                break;
            case 0:
                return 0;
                break;
            default:
                std::cout << "Введена неизвестная команда\n";
                break;
        }

        std::cout << "Желаете продолжить пользоваться программой? [y/n] ";
        std::cin >> userChoice;
    }
    return 0;
}
