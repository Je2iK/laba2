#ifndef ROMANCONVERTER_H
#define ROMANCONVERTER_H

#include <string>
#include "../structures/array_triangle.h"
#include "../structures/hashtable.h"

using namespace std;

class RomanConverter {
private:
    HashTable<int, string> ht;          
    Array<int> values;   
public:
    RomanConverter();
    string intToRoman(long long num);
};

#endif