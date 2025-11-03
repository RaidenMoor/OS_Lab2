#include "stack.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
Stack<T>::Stack() : top(nullptr), size(0) {}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
Stack<T>::Stack(const Stack& other) : top(nullptr), size(0) {
    copyFrom(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
void Stack<T>::copyFrom(const Stack& other) {
    if (other.isEmpty()) {
        return;
    }

      Stack<T> temp;
    Node* current = other.top;
    while (current != nullptr) {
        temp.push(current->data);
        current = current->next;
    }

      while (!temp.isEmpty()) {
        push(temp.pop());
    }
}

// Добавление элемента в стек
template <typename T>
void Stack<T>::push(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    size++;
}

// Извлечение элемента из стека
template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw runtime_error("Стэк пустой");
    }

    Node* temp = top;
    T value = top->data;
    top = top->next;
    delete temp;
    size--;

    return value;
}

// Просмотр верхнего элемента
template <typename T>
T& Stack<T>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Стэк пустой");
    }
    return top->data;
}


template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

// Получение размера стека
template <typename T>
size_t Stack<T>::getSize() const {
    return size;
}

// Очистка стека
template <typename T>
void Stack<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

// Сохранение стека в файл
template <typename T>
bool Stack<T>::saveToFile(const wchar_t* filename) const {
    HANDLE hFile = CreateFile(
        filename,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

        DWORD bytesWritten;
    if (!WriteFile(hFile, &size, sizeof(size_t), &bytesWritten, NULL)) {
        CloseHandle(hFile);
        return false;
    }

   
    Stack<T> tempStack = *this;
    Stack<T> reverseStack;

      while (!tempStack.isEmpty()) {
        reverseStack.push(tempStack.pop());
    }

       while (!reverseStack.isEmpty()) {
        T value = reverseStack.pop();
        if (!WriteFile(hFile, &value, sizeof(T), &bytesWritten, NULL)) {
            CloseHandle(hFile);
            return false;
        }
    }

    CloseHandle(hFile);
    return true;
}

// Загрузка стека из файла
template <typename T>
bool Stack<T>::loadFromFile(const wchar_t* filename) {
    HANDLE hFile = CreateFile(
        filename,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

       clear();

    DWORD bytesRead;
    size_t fileSize;
    if (!ReadFile(hFile, &fileSize, sizeof(size_t), &bytesRead, NULL)) {
        CloseHandle(hFile);
        return false;
    }

    for (size_t i = 0; i < fileSize; i++) {
        T value;
        if (!ReadFile(hFile, &value, sizeof(T), &bytesRead, NULL)) {
            CloseHandle(hFile);
            clear();
            return false;
        }
        push(value);
    }

    CloseHandle(hFile);
    return true;
}

template class Stack<int>;
template class Stack<double>;