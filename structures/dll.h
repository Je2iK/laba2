#ifndef DLL_H
#define DLL_H
#include <iostream>
#include "array_triangle.h"
#include <fstream>
using namespace std;
template <typename T>
class DoublyLinkedList {
private:
    size_t sz = 0;
public:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(T v) : value(v), prev(nullptr), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size() const {return sz;}
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), sz(0){
        Node* cur = other.head;
        while(cur){
            addTail(cur->value);
            cur = cur->next;
        }
    }
    DoublyLinkedList& operator=(const DoublyLinkedList& other){
        if (this == &other) return *this;
        clear();
        Node* cur = other.head;
        while (cur){
            addTail(cur->value);
            cur = cur->next;
        }
        return *this;
    }
    ~DoublyLinkedList();
    void toArray(Array<T>& out);
    // Добавление
    void addHead(T value);
    void addTail(T value);
    void addBeforeValue(T target, T value); // перед узлом со значением target
    void addAfterValue(T target, T value);  // после узла со значением target

    // Удаление
    void deleteHead();
    void deleteTail();
    void deleteValue(T value);               // удалить узел со значением value
    void deleteBeforeValue(T target);
    void deleteAfterValue(T target);

    // Поиск и вывод
    bool search(T value) const;
    void readForward() const;
    void readBackward() const;

    // Работа с файлами
    void saveToFile(const string& filename = "txt/dll.txt") const;
    void loadFromFile(const string& filename = "txt/dll.txt");

    // Вспомогательные
    bool isEmpty() const { return head == nullptr; }
    void clear();
    int length() const;
    void mained();
};
#include "dll.tpp"
#endif
