#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>

template<class INF, class FRIEND>
class ListNode {
private:
    INF data;
    ListNode* next;
    ListNode() {
        next = nullptr;
    }
    friend FRIEND;
};

template<class INF>
class MyStack;

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyStack<T>& stack);

template<class INF>
class MyStack {
private:
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node* top;

public:
    MyStack() : top(nullptr) {}
    ~MyStack();
    bool empty() const;
    bool push(INF n);
    bool pop();
    INF topInf() const;
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);


    friend std::ostream& operator<< <INF>(std::ostream& os, const MyStack<INF>& stack);


    INF getNodeData(const Node* node) const { return node->data; }
    Node* getNodeNext(const Node* node) const { return node->next; }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyStack<T>& stack) {
    typename MyStack<T>::Node* current = stack.top;
    while (current != nullptr) {
        os << stack.getNodeData(current) << " ";
        current = stack.getNodeNext(current);
    }
    return os;
}


template<class INF>
MyStack<INF>::~MyStack() {
    while (!empty()) {
        pop();
    }
}

template<class INF>
bool MyStack<INF>::empty() const {
    return top == nullptr;
}

template<class INF>
bool MyStack<INF>::push(INF n) {
    Node* newNode = new Node();
    newNode->data = n;
    newNode->next = top;
    top = newNode;
    return true;
}

template<class INF>
bool MyStack<INF>::pop() {
    if (empty()) {
        return false;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
    return true;
}

template<class INF>
INF MyStack<INF>::topInf() const {
    if (empty()) {
        throw "Стек пустой";
    }
    return top->data;
}

template<class INF>
MyStack<INF>::MyStack(const MyStack& other) : top(nullptr) {
    if (other.top != nullptr) {
        top = new Node();
        top->data = other.top->data;
        Node* current = top;
        Node* otherCurrent = other.top->next;
        while (otherCurrent != nullptr) {
            current->next = new Node();
            current = current->next;
            current->data = otherCurrent->data;
            otherCurrent = otherCurrent->next;
        }
    }
}

template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack& other) {
    if (this != &other) {
        while (!empty()) {
            pop();
        }
        if (other.top != nullptr) {
            top = new Node();
            top->data = other.top->data;
            Node* current = top;
            Node* otherCurrent = other.top->next;
            while (otherCurrent != nullptr) {
                current->next = new Node();
                current = current->next;
                current->data = otherCurrent->data;
                otherCurrent = otherCurrent->next;
            }
        }
    }
    return *this;
}

#endif // MYSTACK_H