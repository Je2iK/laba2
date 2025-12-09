#include "rom.h"

RomanConverter::RomanConverter() {
    ht.put(1000, "M");
    ht.put(900, "CM");
    ht.put(500, "D");
    ht.put(400, "CD");
    ht.put(100, "C");
    ht.put(90, "XC");
    ht.put(50, "L");
    ht.put(40, "XL");
    ht.put(10, "X");
    ht.put(9, "IX");
    ht.put(5, "V");
    ht.put(4, "IV");
    ht.put(1, "I");

    int vals[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    for (int v : vals)
        values.push_back(v);
}

string RomanConverter::intToRoman(long long num) {
    string result;

    for (int i = 0; i < values.size(); ++i) {
        int val = values[i];
        while (num >= val) {
            num -= val;
            result += ht.get(val);
        }
    }
    return result;
}