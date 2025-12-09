#include "lru.h"
#include <iostream>

CacheNode::CacheNode(int k, int v) : key(k), value(v) {}

LRUCache::LRUCache(int cap) : capacity(cap), size(0) {}

int LRUCache::get(int key) {
    CacheNode* node = table.get(key);
    if (!node) return -1;
    dll.deleteValue(node);
    dll.addHead(node);
    return node->value;
}

void LRUCache::set(int key, int value) {
    CacheNode* node = table.get(key);
    if (node) {
        node->value = value;
        dll.deleteValue(node);
        dll.addHead(node);
        return;
    }

    if (size >= capacity) {
        CacheNode* old = dll.tail->value;
        table.remove(old->key);
        dll.deleteTail();
        delete old;
        size--;
    }

    CacheNode* newNode = new CacheNode(key, value);
    dll.addHead(newNode);
    table.put(key, newNode);
    size++;
}
