#ifndef MYSET_H
#define MYSET_H

#include "MyVector.h"

template<class T>
class MySet;

template<typename T>
std::ostream& operator<<(std::ostream& os, const MySet<T>& set);

template <typename T>
class MySet : public MyVector<T> {
public:
    MySet(size_t initial_size = 1);
    MySet(const MySet& other);

    void add_element(const T& element);
    void delete_element(const T& element);
    bool is_element(const T& element) const;
    void sort();
    int q_find(const T& element) const;

    MySet<T> operator+(const MySet<T>& other) const;
    MySet<T> operator-(const MySet<T>& other) const;
    MySet<T> operator*(const MySet<T>& other) const;

    MySet& operator+=(const MySet& other);
    MySet& operator-=(const MySet& other);
    MySet& operator*=(const MySet& other);

    bool operator==(const MySet<T>& other) const;
    friend std::ostream& operator<< <>(std::ostream& os, const MySet& set);
};

template <typename T>
MySet<T>::MySet(size_t initial_size) : MyVector<T>(initial_size) {}
    
template <typename T>
MySet<T>::MySet(const MySet& other) : MyVector<T>(other) {}

template <typename T>
void MySet<T>::add_element(const T& element) {
    if (this->find(element) == -1) {
        MyVector<T>::add_element(element);
        sort();
    }
}

template <typename T>
void MySet<T>::delete_element(const T& element) {
    int index = this->find(element);
    if (index != -1) {
        MyVector<T>::delete_element(index);
    }
}

template <typename T>
bool MySet<T>::is_element(const T& element) const {
    return this->find(element) != -1;
}

template <typename T>
void MySet<T>::sort() {
    for (size_t i = 0; i < this->size - 1; ++i) {
        for (size_t j = 0; j < this->size - i - 1; ++j) {
            if (this->pdata[j] > this->pdata[j + 1]) {
                T temp = this->pdata[j];
                this->pdata[j] = this->pdata[j + 1];
                this->pdata[j + 1] = temp;
            }
        }
    }
}

template <typename T>
int MySet<T>::q_find(const T& element) const {
    int left = 0;
    int right = this->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (this->pdata[mid] == element) {
            return mid;
        }
        if (this->pdata[mid] < element) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

template <typename T>
MySet<T> MySet<T>::operator+(const MySet<T>& other) const {
    MySet<T> result = *this;
    for (size_t i = 0; i < other.getSize(); ++i) {
        result.add_element(other[i]);
    }
    return result;
}

template <typename T>
MySet<T> MySet<T>::operator-(const MySet<T>& other) const {
    MySet<T> result;
    for (size_t i = 0; i < this->size; ++i) {
        if (!other.is_element(this->pdata[i])) {
            result.add_element(this->pdata[i]);
        }
    }
    return result;
}

template <typename T>
MySet<T> MySet<T>::operator*(const MySet<T>& other) const {
    MySet<T> result;
    for (size_t i = 0; i < this->size; ++i) {
        if (other.is_element(this->pdata[i])) {
            result.add_element(this->pdata[i]);
        }
    }
    return result;
}

template <typename T>
MySet<T>& MySet<T>::operator+=(const MySet& other) {
    *this = *this + other;
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator-=(const MySet& other) {
    *this = *this - other;
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator*=(const MySet& other) {
    *this = *this * other;
    return *this;
}

template <typename T>
bool MySet<T>::operator==(const MySet<T>& other) const {
    if (this->size != other.size) return false;
    for (size_t i = 0; i < this->size; ++i) {
        if (this->pdata[i] != other.pdata[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MySet<T>& set) {
    for (size_t i = 0; i < set.getSize(); ++i) {
        os << set[i] << " ";
    }
    return os;
}

template<class T>
class MySet;

template<typename T>
std::ostream& operator<<(std::ostream& os, const MySet<T>& set);


template <>
class MySet<const char*> : public MyVector<const char*> {
public:
    MySet(size_t initial_size = 1);
    MySet(const MySet& other);
    MySet(const char* initial_element);

    void add_element(const char* element);
    void delete_element(const char* element);
    bool is_element(const char* element) const;
    void sort();
    int q_find(const char* element) const;

    MySet operator+(const MySet& other) const;
    MySet operator-(const MySet& other) const;
    MySet operator*(const MySet& other) const;

    MySet& operator+=(const MySet& other);
    MySet& operator-=(const MySet& other);
    MySet& operator*=(const MySet& other);

    bool operator==(const MySet& other) const;

    friend std::ostream& operator<< <>(std::ostream& os, const MySet& set);
};

MySet<const char*>::MySet(size_t initial_size) : MyVector<const char*>(initial_size) {}
    
MySet<const char*>::MySet(const MySet& other) : MyVector<const char*>(other) {}
    
MySet<const char*>::MySet(const char* initial_element) : MyVector<const char*>(1) {
    this->add_element(initial_element); 
}

void MySet<const char*>::add_element(const char* element) {
    if (this->find(element) == -1) {
        MyVector<const char*>::add_element(element);
        sort();
    }
}

void MySet<const char*>::delete_element(const char* element) {
    int index = this->find(element);
    if (index != -1) {
        MyVector<const char*>::delete_element(index);
    }
}

bool MySet<const char*>::is_element(const char* element) const {
    return this->find(element) != -1;
}

void MySet<const char*>::sort() {
    for (size_t i = 0; i < this->size - 1; ++i) {
        for (size_t j = 0; j < this->size - i - 1; ++j) {
            if (strcmp(this->pdata[j], this->pdata[j + 1]) > 0) {
                const char* temp = this->pdata[j];
                this->pdata[j] = this->pdata[j + 1];
                this->pdata[j + 1] = temp;
            }
        }
    }
}

int MySet<const char*>::q_find(const char* element) const {
    int left = 0;
    int right = this->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(this->pdata[mid], element);
        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

MySet<const char*> MySet<const char*>::operator+(const MySet& other) const {
    MySet result = *this;
    for (size_t i = 0; i < other.getSize(); ++i) {
        result.add_element(other[i]);
    }
    return result;
}

MySet<const char*> MySet<const char*>::operator-(const MySet& other) const {
    MySet result;
    for (size_t i = 0; i < this->size; ++i) {
        if (!other.is_element(this->pdata[i])) {
            result.add_element(this->pdata[i]);
        }
    }
    return result;
}

MySet<const char*> MySet<const char*>::operator*(const MySet& other) const {
    MySet result;
    for (size_t i = 0; i < this->size; ++i) {
        if (other.is_element(this->pdata[i])) {
            result.add_element(this->pdata[i]);
        }
    }
    return result;
}

bool MySet<const char*>::operator==(const MySet& other) const {
    if (this->size != other.size) return false;
    for (size_t i = 0; i < this->size; ++i) {
        if (strcmp(this->pdata[i], other.pdata[i]) != 0) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const MySet<const char*>& set) {
    for (size_t i = 0; i < set.getSize(); ++i) {
        os << set[i] << " ";
    }
    return os;
}

#endif // MYSET_H