#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include "../structures/dll.h"
#include "../structures/hashtable.h"

using namespace std;

struct HuffNode {
    char ch;
    int freq;
    HuffNode* left;
    HuffNode* right;

    HuffNode(char c, int f);
    HuffNode(HuffNode* l, HuffNode* r);
};

struct HuffmanResult {
    HashTable<char, string> codes;
    HuffNode* root;
};

void insertSorted(DoublyLinkedList<HuffNode*>& list, HuffNode* node);
void buildCodes(HuffNode* root, const string& prefix, HashTable<char, string>& codes);
HuffmanResult huffman(const string& text);
string huffmanDecode(const string& encoded, HuffNode* root);

#endif

