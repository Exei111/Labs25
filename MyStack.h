#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <stdexcept>

template<class INF, class FRIEND>
class ListNode {
private:
    INF d;
    ListNode* next;
    ListNode() : next(nullptr) {}
    friend FRIEND;
};

template<class INF>
class MyStack {
public:
    class Node {
    public:
        INF d;
        Node* next;
        Node(INF data, Node* n = nullptr) : d(data), next(n) {}
    };

private:
    Node* top;

public:
    MyStack() : top(nullptr) {}
    ~MyStack();

    bool empty() const { return top == nullptr; }
    bool push(INF n);
    bool pop();
    INF topInf() const;

    Node* getTopNode() const { return top; }
    static Node* getNextNode(Node* node) { return node ? node->next : nullptr; }
    static INF getNodeValue(Node* node) { return node ? node->d : INF(); }

    MyStack(const MyStack&) = delete;
    MyStack& operator=(const MyStack&) = delete;
};

template<class INF>
MyStack<INF>::~MyStack() {
    while (!empty()) {
        pop();
    }
}

template<class INF>
bool MyStack<INF>::push(INF n) {
    Node* newNode = new Node(n, top);
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
        throw std::runtime_error("Stack is empty!");
    }
    return top->d;
}

#endif // MYSTACK_H