#ifndef SET_CONNECT_H
#define SET_CONNECT_H

#include <iostream>
#include "../structures/dll.h"
#include "../structures/array_triangle.h" 
using namespace std;

class Set {
private:
    static const int TABLE_SIZE = 101; 
    Array<DoublyLinkedList<int>> table;
    int hashFunction(int key) const;
    void collectElements(const DoublyLinkedList<int>& list, Array<int>& out);

public:
    Set();

    void add(int value);                      
    bool contains(int value) const;           
    int intersectionCount(const Set& other);  
    void print();
    void remove(int value);
    void saveToFile(const string& path);
    void loadFromFile(const string& path);                         
};

void findMaxIntersection(Array<Set>& sets);

#endif
