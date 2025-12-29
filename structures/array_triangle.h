#ifndef ARRAY_TRIANGLE_H
#define ARRAY_TRIANGLE_H
#include <iostream>
using namespace std;

struct Block {
    long long width;
    long long height;
};

template <typename T>
class Array {
private:
    T* data;
    int capacity;
    int length;

    void resize(int newCap) {
        T* newData = new T[newCap];
        for (int i = 0; i < length; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    Array(int initCap = 10) {
        capacity = initCap;
        length = 0;
        data = new T[capacity];
    }

    // Конструктор копирования
    Array(const Array& other) {
        capacity = other.capacity;
        length = other.length;
        data = new T[capacity];
        for (int i = 0; i < length; ++i)
            data[i] = other.data[i];
    }

    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            length = other.length;
            data = new T[capacity];
            for (int i = 0; i < length; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length >= capacity)
            resize(capacity * 2);
        data[length++] = value;
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int size() const {
        return length;
    }
};

void quickSort(Block* arr, int left, int right);
long long maxPyramidHeight(Array<Block>& blocks);

#endif 