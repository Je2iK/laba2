#include "huffman.h"
#include <iostream>

HuffNode::HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
HuffNode::HuffNode(HuffNode* l, HuffNode* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}

void insertSorted(DoublyLinkedList<HuffNode*>& list, HuffNode* node) {
    auto cur = list.head;
    while (cur && cur->value->freq <= node->freq) cur = cur->next;

    if (!cur) list.addTail(node);
    else list.addBeforeValue(cur->value, node);
}

void buildCodes(HuffNode* root, const string& prefix, HashTable<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        string code = prefix.empty() ? "0" : prefix;
        codes.put(root->ch, code);
        return;
    }
    if (root->left) buildCodes(root->left, prefix + "0", codes);
    if (root->right) buildCodes(root->right, prefix + "1", codes);
}

HuffmanResult huffman(const string& text) {
    int freq[256] = {0};
    for (char c : text) freq[(unsigned char)c]++;

    DoublyLinkedList<HuffNode*> list;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            insertSorted(list, new HuffNode((char)i, freq[i]));
        }
    }

    // Особый случай: только один уникальный символ
    if (list.length() == 1) {
        HashTable<char, string> codes;
        codes.put(list.head->value->ch, "0");
        HuffmanResult result;
        result.codes = codes;
        result.root = list.head->value;
        return result;
    }

    while (list.length() > 1) {
        HuffNode* first = list.head->value;
        HuffNode* second = list.head->next->value;

        HuffNode* parent = new HuffNode(first, second);

        list.deleteHead();
        list.deleteHead();

        insertSorted(list, parent);
    }

    HuffNode* root = list.head->value;

    HashTable<char, string> codes;
    buildCodes(root, "", codes);
    
    HuffmanResult result;
    result.codes = codes;
    result.root = root;
    return result;
}

string huffmanDecode(const string& encoded, HuffNode* root) {
    if (!root) return "";
    
    string result;
    HuffNode* current = root;
    
    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        // Если достигли листа
        if (!current->left && !current->right) {
            result += current->ch;
            current = root; // Возвращаемся к корню
        }
    }
    
    return result;
}
