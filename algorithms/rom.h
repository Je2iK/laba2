#ifndef ROMANCONVERTER_H
#define ROMANCONVERTER_H

#include <string>
#include <chrono>
#include "../structures/array_triangle.h"
#include "../structures/hashtable.h"

using namespace std;

template <typename K, typename V>
class HashTableOpenAddressing {
private:
    static const int SIZE = 101;
    Array<K> keys;
    Array<V> values;
    Array<bool> used;
    
    int hash(K key) const {
        unsigned char uc = (unsigned char)key;
        return uc % SIZE;
    }
    
public:
    HashTableOpenAddressing() {
        for (int i = 0; i < SIZE; ++i) {
            keys.push_back(K());
            values.push_back(V());
            used.push_back(false);
        }
    }
    
    void put(K key, const V& value) {
        int idx = hash(key);
        while (used[idx]) {
            if (keys[idx] == key) {
                values[idx] = value;
                return;
            }
            idx = (idx + 1) % SIZE;
        }
        keys[idx] = key;
        values[idx] = value;
        used[idx] = true;
    }
    
    V get(K key) {
        int idx = hash(key);
        while (used[idx]) {
            if (keys[idx] == key) {
                return values[idx];
            }
            idx = (idx + 1) % SIZE;
        }
        return V();
    }
};

class RomanConverter {
private:
    HashTable<int, string> ht;          
    Array<int> values;   
public:
    RomanConverter();
    string intToRoman(long long num);
    string intToRomanChaining(long long num);
    string intToRomanOpenAddressing(long long num);
    void benchmarkHashTables(long long num);
};

#endif
