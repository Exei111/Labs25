#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <cstring>

template<class T>
class MyVector;

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& set);

template <typename T>
class MyVector {
protected:
    size_t max_size;
    size_t size;
    T* pdata;

public:
    MyVector(size_t initial_size = 1);
    MyVector(const MyVector& other);
    ~MyVector();

    void add_element(const T& element);
    void delete_element(size_t index);
    int find(const T& element) const;
    void resize(size_t new_size);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    MyVector& operator=(const MyVector& other);

    size_t getSize() const;

    friend std::ostream& operator<< <>(std::ostream& os, const MyVector<T>& set);
};

template <typename T>
MyVector<T>::MyVector(size_t initial_size) : max_size(initial_size), size(0) {
    pdata = new T[max_size];
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : max_size(other.max_size), size(other.size) {
    pdata = new T[max_size];
    for (size_t i = 0; i < size; ++i) {
        pdata[i] = other.pdata[i];
    }
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] pdata;
}

template <typename T>
void MyVector<T>::add_element(const T& element) {
    if (size >= max_size) {
        resize(max_size * 2);
    }
    pdata[size++] = element;
}

template <typename T>
void MyVector<T>::delete_element(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }
    --size;
    if (size < max_size / 4 && max_size > 1) {
        resize(max_size / 2);
    }
}

template <typename T>
int MyVector<T>::find(const T& element) const {
    for (size_t i = 0; i < size; ++i) {
        if (pdata[i] == element) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void MyVector<T>::resize(size_t new_size) {
    T* new_data = new T[new_size];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_data;
    max_size = new_size;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    return pdata[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    return pdata[index];
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this != &other) {
        delete[] pdata;
        max_size = other.max_size;
        size = other.size;
        pdata = new T[max_size];
        for (size_t i = 0; i < size; ++i) {
            pdata[i] = other.pdata[i];
        }
    }
    return *this;
}

template <typename T>
size_t MyVector<T>::getSize() const {
    return size;
}

template<class T>
class MyVector;

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec);

template <>
class MyVector<const char*> {
protected:
    size_t max_size;
    size_t size;
    const char** pdata;

public:
    MyVector(size_t initial_size = 1);
    MyVector(const MyVector& other);
    MyVector(const char* initial_element);
    ~MyVector();

    void add_element(const char* element);
    void delete_element(size_t index);
    int find(const char* element) const;
    void resize(size_t new_size);

    const char*& operator[](size_t index);
    const char*& operator[](size_t index) const;

    MyVector& operator=(const MyVector& other);

    size_t getSize() const;

    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec);
};

MyVector<const char*>::MyVector(size_t initial_size) : max_size(initial_size), size(0) {
    pdata = new const char*[max_size];
}

MyVector<const char*>::MyVector(const MyVector& other) : max_size(other.max_size), size(other.size) {
    pdata = new const char*[max_size];
    for (size_t i = 0; i < size; ++i) {
        pdata[i] = other.pdata[i];
    }
}

MyVector<const char*>::MyVector(const char* initial_element) : max_size(1), size(1) {
    pdata = new const char*[max_size];
    pdata[0] = new char[strlen(initial_element) + 1];
    strcpy(const_cast<char*>(pdata[0]), initial_element);
}

MyVector<const char*>::~MyVector() {
    delete[] pdata;
}

void MyVector<const char*>::add_element(const char* element) {
    if (size >= max_size) {
        resize(max_size * 2);
    }
    pdata[size++] = element;
}

void MyVector<const char*>::delete_element(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }
    --size;
    if (size < max_size / 4 && max_size > 1) {
        resize(max_size / 2);
    }
}

int MyVector<const char*>::find(const char* element) const {
    for (size_t i = 0; i < size; ++i) {
        if (strcmp(pdata[i], element) == 0) {
            return i;
        }
    }
    return -1;
}

void MyVector<const char*>::resize(size_t new_size) {
    const char** new_data = new const char*[new_size];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_data;
    max_size = new_size;
}

const char*& MyVector<const char*>::operator[](size_t index) {
    return pdata[index];
}

const char*& MyVector<const char*>::operator[](size_t index) const {
    return pdata[index];
}

MyVector<const char*>& MyVector<const char*>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] pdata;
        max_size = other.max_size;
        size = other.size;
        pdata = new const char*[max_size];
        for (size_t i = 0; i < size; ++i) {
            pdata[i] = other.pdata[i];
        }
    }
    return *this;
}

size_t MyVector<const char*>::getSize() const {
    return size;
}

std::ostream& operator<<(std::ostream& os, const MyVector<const char*>& vec) {
    for (size_t i = 0; i < vec.size; ++i) {
        os << vec.pdata[i] << " ";
    }
    return os;
}
#endif // MYVECTOR_H