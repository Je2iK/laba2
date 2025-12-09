#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
using namespace std;

// ===== Класс Стек =====
class Stack {
private:
    static const int MAX_SIZE = 100;
    double items[MAX_SIZE];
    int top;

public:
    Stack();                  // Конструктор
    bool isEmpty() const;     // Проверка пустоты
    bool isFull() const;      // Проверка переполнения
    void push(double value);  // Добавление элемента
    double pop();             // Извлечение элемента
    double peek() const;      // Просмотр верхнего элемента
};

#endif

