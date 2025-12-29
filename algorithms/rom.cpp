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
\

string RomanConverter::intToRomanChaining(long long num) {
    HashTable<int, string> htc;
    htc.put(1000, "M"); htc.put(900, "CM"); htc.put(500, "D"); htc.put(400, "CD");
    htc.put(100, "C"); htc.put(90, "XC"); htc.put(50, "L"); htc.put(40, "XL");
    htc.put(10, "X"); htc.put(9, "IX"); htc.put(5, "V"); htc.put(4, "IV"); htc.put(1, "I");
    
    string result;
    for (int i = 0; i < values.size(); ++i) {
        int val = values[i];
        while (num >= val) {
            num -= val;
            result += htc.get(val);
        }
    }
    return result;
}

string RomanConverter::intToRomanOpenAddressing(long long num) {
    HashTableOpenAddressing<int, string> hto;
    hto.put(1000, "M"); hto.put(900, "CM"); hto.put(500, "D"); hto.put(400, "CD");
    hto.put(100, "C"); hto.put(90, "XC"); hto.put(50, "L"); hto.put(40, "XL");
    hto.put(10, "X"); hto.put(9, "IX"); hto.put(5, "V"); hto.put(4, "IV"); hto.put(1, "I");
    
    string result;
    for (int i = 0; i < values.size(); ++i) {
        int val = values[i];
        while (num >= val) {
            num -= val;
            result += hto.get(val);
        }
    }
    return result;
}

void RomanConverter::benchmarkHashTables(long long num) {
    cout << "Сравнение хеш-таблиц для преобразования " << num << "\n";
    
    int iterations = 50000;
    
    // Создание таблиц один раз
    HashTable<int, string> htc;
    htc.put(1000, "M"); htc.put(900, "CM"); htc.put(500, "D"); htc.put(400, "CD");
    htc.put(100, "C"); htc.put(90, "XC"); htc.put(50, "L"); htc.put(40, "XL");
    htc.put(10, "X"); htc.put(9, "IX"); htc.put(5, "V"); htc.put(4, "IV"); htc.put(1, "I");
    
    HashTableOpenAddressing<int, string> hto;
    hto.put(1000, "M"); hto.put(900, "CM"); hto.put(500, "D"); hto.put(400, "CD");
    hto.put(100, "C"); hto.put(90, "XC"); hto.put(50, "L"); hto.put(40, "XL");
    hto.put(10, "X"); hto.put(9, "IX"); hto.put(5, "V"); hto.put(4, "IV"); hto.put(1, "I");
    
    // Тест цепочек
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        long long temp_num = num;
        string result;
        for (int j = 0; j < values.size(); ++j) {
            int val = values[j];
            while (temp_num >= val) {
                temp_num -= val;
                result += htc.get(val);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto chain_time = chrono::duration<double>(end - start).count();
    
    // Тест открытой адресации
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        long long temp_num = num;
        string result;
        for (int j = 0; j < values.size(); ++j) {
            int val = values[j];
            while (temp_num >= val) {
                temp_num -= val;
                result += hto.get(val);
            }
        }
    }
    end = chrono::high_resolution_clock::now();
    auto open_time = chrono::duration<double>(end - start).count();
    
    cout << "Размер таблиц: 101 (коэффициент загрузки: " << (13.0/101) << ")\n";
    cout << "Итераций: " << iterations << "\n";
    cout << "Метод цепочек: " << chain_time << " сек\n";
    cout << "Открытая адресация: " << open_time << " сек\n";
    cout << "Соотношение: " << (chain_time / open_time) << "\n";
}