#include <iostream>
#include <windows.h>
#include "stack.h"

using namespace std;

void testIntStack() {
    cout << "Проверка функций стэка целых чисел" << endl;

    Stack<int> stack;

  
    cout << "Добавление в стек элементов 10, 20, 30" << endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Размер стека: " << stack.getSize() << endl;
    cout << "Последний добавленный элемент: " << stack.peek() << endl;

    // Тестируем сохранение в файл
    if (stack.saveToFile(L"int_stack.bin")) {
        cout << "Объект (стэк) успешно сохранен в файл" << endl;
    }
    else {
        cout << "Не удалось сохранить объект в файл" << endl;
    }

    cout << "Извлечение элементов: ";
    while (!stack.isEmpty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;

    cout << "Размер стэка после извлечения элементов: " << stack.getSize() << endl;

    
    if (stack.loadFromFile(L"int_stack.bin")) {
        cout << "Объект успешно считан из файла" << endl;
        cout << "Размерность загруженного стэка: " << stack.getSize() << endl;
        cout << "Вырхний элемент загруженного стэка: " << stack.peek() << endl;
    }
    else {
        cout << "Ошибка загрузки объекта из файла" << endl;
    }

    
    stack.clear();
    cout << "Размерность стэка после очистки: " << stack.getSize() << endl;
}

void testDoubleStack() {
    cout << "\nПроверка функций стэка вещественных чисел" << endl;

    Stack<double> stack;

    stack.push(1.1);
    stack.push(2.2);
    stack.push(3.3);

    cout << "Размерность стэка: " << stack.getSize() << endl;
    cout << "Верхний элемент стэка: " << stack.peek() << endl;

    Stack<double> stackCopy = stack;
    cout << "Размерность скопированного стэка: " << stackCopy.getSize() << endl;

    Stack<double> stackAssigned;
    stackAssigned = stack;
    cout << "Размерность стжка, созданного через оператор присваивания: " << stackAssigned.getSize() << endl;
}

void testErrorHandling() {
    cout << "\nДемонстрация сообщений об ошибках" << endl;

    Stack<int> stack;

    try {
        stack.pop(); 
    }
    catch (const runtime_error& e) {
        cout << "Обнаружена ошибка: " << e.what() << endl;
    }

    try {
        stack.peek(); 
    }
    catch (const runtime_error& e) {
        cout << "Обнаружена ошибка: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №2 по дисциплине \"Операционные системы\"" << endl;
    cout << "Выполнила стундентка группы 6401-020302D Гусева Мария" << endl;
    cout << "Вариант №7: реализовать стек на основе связного списка" << endl;
    testIntStack();
    testDoubleStack();
    testErrorHandling();

 
    return 0;
}