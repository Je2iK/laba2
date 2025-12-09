#include "huffman.h"
#include <iostream>

HuffNode::HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
HuffNode::HuffNode(HuffNode* l, HuffNode* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}

void insertSorted(DoublyLinkedList<HuffNode*>& list, HuffNode* node) {
    auto cur = list.head;
    while (cur && cur->value->freq < node->freq) cur = cur->next;

    if (!cur) list.addTail(node);
    else list.addBeforeValue(cur->value, node);
}

void buildCodes(HuffNode* root, const string& prefix, HashTable<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right && root->ch != 0) {
        codes.put(root->ch, prefix);
        return;
    }
    buildCodes(root->left, prefix + "0", codes);
    buildCodes(root->right, prefix + "1", codes);
}

HashTable<char, string> huffman(const string& text) {
    int freq[256] = {0};
    for (char c : text) freq[(unsigned char)c]++;

    DoublyLinkedList<HuffNode*> list;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) list.addTail(new HuffNode((char)i, freq[i]));
    }

    DoublyLinkedList<HuffNode*> sortedList;
    auto cur = list.head;
    while (cur) {
        insertSorted(sortedList, cur->value);
        cur = cur->next;
    }

    while (sortedList.length() > 1) {
        HuffNode* first = sortedList.head->value;
        HuffNode* second = sortedList.head->next->value;

        HuffNode* parent = new HuffNode(first, second);

        sortedList.deleteHead();
        sortedList.deleteHead();

        insertSorted(sortedList, parent);
    }

    HuffNode* root = sortedList.head->value;

    HashTable<char, string> codes;
    buildCodes(root, "", codes);
    return codes;
}
