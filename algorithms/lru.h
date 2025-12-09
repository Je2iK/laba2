#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "../structures/dll.h"
#include "../structures/hashtable.h"
#include <string>

using namespace std;

struct CacheNode {
    int key;
    int value;
    CacheNode(int k, int v);
};

class LRUCache {
private:
    int capacity;
    int size;
    DoublyLinkedList<CacheNode*> dll;
    HashTable<int, CacheNode*> table;

public:
    LRUCache(int cap);
    int get(int key);
    void set(int key, int value);
};

#endif
