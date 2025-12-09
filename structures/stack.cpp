#include "stack.h"
#include <cctype>   // для isdigit
#include <iostream>
using namespace std;

//////////////////// Stack ////////////////////
Stack::Stack() : top(-1) {}

bool Stack::isEmpty() const { return top == -1; }
bool Stack::isFull() const { return top == MAX_SIZE - 1; }

void Stack::push(double value) {
    if (isFull()) {
        cout << "Ошибка: стек переполнен!" << endl;
        return;
    }
    items[++top] = value;
}

double Stack::pop() {
    if (isEmpty()) {
        cout << "Ошибка: стек пуст!" << endl;
        return 0;
    }
    return items[top--];
}

double Stack::peek() const {
    if (isEmpty()) {
        cout << "Ошибка: стек пуст!" << endl;
        return 0;
    }
    return items[top];
}

