#include <iostream>
#include "MyVector.h"
#include "MySet.h"

int main() {
    setlocale(LC_ALL, "Russian");

    MyVector<const char*> v("Hello!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    MyVector<const char*> v1 = v;
    std::cout << "Вектор v1: " << v1 << std::endl;
    for (int i = 0; i < v1.getSize(); i++)
        v1.delete_element(0);
    std::cout << "Вектор v1: " << v1 << std::endl;
    MySet<const char*> s, s1, s2;
    s.add_element("Yes");
    s.add_element("Привет!");
    s.add_element("No");
    const char *str = "Hello!";
    s.add_element(str);
    std::cout << "Множество s: " << s << std::endl;
    s1.add_element("Cat");
    s1.add_element("No");
    s1.add_element("Привет!");
    std::cout << "Множество s1: " << s1 << std::endl;
    s2 = s1 - s;
    std::cout << "Множество s2=s1-s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s - s1;
    std::cout << "Множество s2=s-s1: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 + s;
    std::cout << "Множество s2=s1+s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 * s;
    std::cout << "Множество s2=s1*s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    MySet<const char*> s3 = s2;
    std::cout << "Множество s3=s2: " << s3 << std::endl;
    if (s3 == s2)
        std::cout << "Множество s3=s2\n";
    else
        std::cout << "Множество s3!=s2\n";
    if (s3 == s1)
        std::cout << "Множество s3=s1\n";
    else
        std::cout << "Множество s3!=s1\n";
    if (s1 == s3)
        std::cout << "Множество s1=s3\n";
    else
        std::cout << "Множество s1!=s3\n";

    MySet<int> set1;
    set1.add_element(1);
    set1.add_element(4);
    set1.add_element(5);
    set1.add_element(6);

    MySet<int> set2;
    set2.add_element(1);
    set2.add_element(2);
    set2.add_element(3);
    set2.add_element(4);

    MySet<int> union_set = set1 + set2;
    std::cout << "Объединение: " << union_set << std::endl;

    MySet<int> difference_set = set1 - set2;
    std::cout << "Разность: " << difference_set << std::endl;

    MySet<int> intersection_set = set1 * set2;
    std::cout << "Пересечение: " << intersection_set << std::endl;

    std::cout << "set1 == set2: " << (set1 == set2) << std::endl;

    return 0;
}