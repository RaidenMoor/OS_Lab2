#pragma once
#ifndef STACK_H
#define STACK_H

#include <windows.h>

template <typename T>
class Stack {
private:
   
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top;  // Вершина стека
    size_t size; // Текущий размер стека

public:
   
    Stack();
    Stack(const Stack& other);
    ~Stack();

    
    Stack& operator=(const Stack& other);

    
    void push(const T& value);
    T pop();
    T& peek() const;
    bool isEmpty() const;
    size_t getSize() const;
    void clear();

    
    bool saveToFile(const wchar_t* filename) const;
    bool loadFromFile(const wchar_t* filename);

private:
    
    void copyFrom(const Stack& other);
};

template class Stack<int>;
template class Stack<double>;

#endif