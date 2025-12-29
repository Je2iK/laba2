#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>

using namespace std;

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;
    HashEntry* next;
    HashEntry(K k, const V& v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashTable {
private:
    static const int SIZE = 101;
    HashEntry<K, V>* table[SIZE];

    int hash(K key) const {
        unsigned char uc = (unsigned char)key;
        return uc % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; ++i) table[i] = nullptr;
    }

    // Конструктор копирования
    HashTable(const HashTable& other) {
        for (int i = 0; i < SIZE; ++i) table[i] = nullptr;
        for (int i = 0; i < SIZE; ++i) {
            HashEntry<K, V>* e = other.table[i];
            while (e) {
                put(e->key, e->value);
                e = e->next;
            }
        }
    }

    // Оператор присваивания
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            // Очищаем текущую таблицу
            for (int i = 0; i < SIZE; ++i) {
                HashEntry<K, V>* e = table[i];
                while (e) {
                    HashEntry<K, V>* next = e->next;
                    delete e;
                    e = next;
                }
                table[i] = nullptr;
            }
            // Копируем из другой таблицы
            for (int i = 0; i < SIZE; ++i) {
                HashEntry<K, V>* e = other.table[i];
                while (e) {
                    put(e->key, e->value);
                    e = e->next;
                }
            }
        }
        return *this;
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; ++i) {
            HashEntry<K, V>* e = table[i];
            while (e) {
                HashEntry<K, V>* next = e->next;
                delete e;
                e = next;
            }
        }
    }

    void put(K key, const V& value) {
        int idx = hash(key);
        HashEntry<K, V>* e = table[idx];
        while (e) {
            if (e->key == key) {
                e->value = value;
                return;
            }
            e = e->next;
        }
        HashEntry<K, V>* newEntry = new HashEntry<K, V>(key, value);
        newEntry->next = table[idx];
        table[idx] = newEntry;
    }

    V get(K key) {
        int idx = hash(key);
        HashEntry<K, V>* e = table[idx];
        while (e) {
            if (e->key == key) return e->value;
            e = e->next;
        }
        return V();
    }

    void remove(K key) {
        int idx = hash(key);
        HashEntry<K, V>* e = table[idx];
        HashEntry<K, V>* prev = nullptr;
        while (e) {
            if (e->key == key) {
                if (prev) prev->next = e->next;
                else table[idx] = e->next;
                delete e;
                return;
            }
            prev = e;
            e = e->next;
        }
    }
};

#endif
