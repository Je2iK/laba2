#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "structures/stack.h"
#include "structures/dll.h"
#include "algorithms/huffman.h"
#include "algorithms/polish.h"
#include "algorithms/lru.h"
#include "algorithms/set_connect.h"
#include "algorithms/rom.h"
#include "structures/array_triangle.h"
using namespace std;



int main(int argc, char* argv[]) {
    cout << "1. Postfix (обратная польская нотация)" << endl;
    cout << "2. Set (операции с множеством)" << endl;
    cout << "3. Set_connect (пересечение множеств)" << endl;
    cout << "4. Array_triangle (пирамида из блоков)" << endl;
    cout << "5. Huffman (кодирование строки)" << endl;
    cout << "6. Roman (конвертация в римские числа)" << endl;
    cout << "7. LRU (кэш с вытеснением)" << endl;
    cout << "Выберите пункт (1-7): ";
    int choice;
    cin >> choice;
    switch(choice){
        case 1:{
            string expression;
            cin >> expression;
            double result = evaluatePostfix(expression);
            cout << "Результат выражения " << expression << " = " << result << endl;
            break;
        }
        case 2:{
            Set mySet;
            string filename = "set_data.txt";
            mySet.loadFromFile(filename);
            
            cout << "\n=== Операции с множеством ===" << endl;
            cout << "Текущее множество: ";
            mySet.print();
            cout << endl;
            
            while (true) {
                cout << "\n1. Добавить элемент (ADD)" << endl;
                cout << "2. Удалить элемент (DEL)" << endl;
                cout << "3. Проверить наличие (CONTAINS)" << endl;
                cout << "4. Показать множество (PRINT)" << endl;
                cout << "5. Очистить множество (CLEAR)" << endl;
                cout << "0. Выход" << endl;
                cout << "Выберите операцию: ";
                
                int op;
                cin >> op;
                
                if (op == 0) break;
                
                switch(op) {
                    case 1: {
                        cout << "Введите значение для добавления: ";
                        int val;
                        cin >> val;
                        mySet.add(val);
                        cout << "Элемент " << val << " добавлен." << endl;
                        break;
                    }
                    case 2: {
                        cout << "Введите значение для удаления: ";
                        int val;
                        cin >> val;
                        mySet.remove(val);
                        cout << "Элемент " << val << " удалён." << endl;
                        break;
                    }
                    case 3: {
                        cout << "Введите значение для проверки: ";
                        int val;
                        cin >> val;
                        if (mySet.contains(val))
                            cout << "Элемент " << val << " присутствует в множестве." << endl;
                        else
                            cout << "Элемент " << val << " отсутствует." << endl;
                        break;
                    }
                    case 4: {
                        cout << "Множество: ";
                        mySet.print();
                        cout << endl;
                        break;
                    }
                    case 5: {
                        mySet = Set();
                        cout << "Множество очищено." << endl;
                        break;
                    }
                    default:
                        cout << "Неизвестная операция!" << endl;
                }
            }
            
            mySet.saveToFile(filename);
            cout << "Множество сохранено в " << filename << endl;
            break;
        }
        case 3:{
            Array<Set> sets;
            for (int i = 0; i < 4; ++i)
                sets.push_back(Set());

            sets[0].add(1);
            sets[0].add(2);
            sets[0].add(3);

            sets[1].add(2);
            sets[1].add(3);
            sets[1].add(4);

            sets[2].add(5);
            sets[2].add(6);
            sets[2].add(7);

            sets[3].add(3);
            sets[3].add(7);
            sets[3].add(5);
            sets[3].add(6);

            findMaxIntersection(sets);
            break;
        }
        case 4:{
            ios::sync_with_stdio(false);
            cin.tie(nullptr);
        
            int N;
            cin >> N;
        
            Array<Block> blocks;
        
            for (int i = 0; i < N; ++i) {
                Block b;
                cin >> b.width >> b.height;
                blocks.push_back(b);
            }
        
            cout << maxPyramidHeight(blocks) << "\n";
            break;
        }
        case 5:{
            string text;
            cout << "Введите строку: ";
            cin.ignore();  // Очистить буфер от \n после ввода числа
            getline(cin, text);
        
            if (text.empty()) {
                cout << "Пустая строка!" << endl;
                break;
            }
        
            HashTable<char, string> codes = huffman(text);
        
            string encoded;
            for (char c : text) {
                string code = codes.get(c);
                if (code.empty()) {
                    cerr << "Ошибка: не найден код для символа '" << c << "'" << endl;
                    break;
                }
                encoded += code;
            }
        
            cout << "\nЗакодированная строка: " << encoded << endl;
            cout << "\nТаблица кодов:" << endl;
        
            for (char c : text) {
                string code = codes.get(c);
                if (!code.empty()) {
                    cout << c << " : " << code << endl;
                    codes.put(c, "");
                }
            }
        
            break;
        }
        case 6:{
            RomanConverter converter;
            long long number;

            cout << "Введите любое положительное число: ";
            cin >> number;

            if (number <= 0) {
                cout << "Ошибка: число должно быть положительным.\n";
                return 1;
            }

            string roman = converter.intToRoman(number);
            cout << "Римская запись: " << roman << endl;
            break;
        }
        case 7:{
            int cap, Q;
            cout << "Введите емкость кэша: ";
            cin >> cap;
            cout << "Введите количество запросов: ";
            cin >> Q;
            cin.ignore();

            LRUCache cache(cap);
            vector<int> output;

            cout << "Введите запросы (SET x y / GET x):\n";
            for (int i = 0; i < Q; ++i) {
                string line;
                getline(cin, line);
                if (line.empty()) {
                    --i;
                    continue;
                }

            stringstream ss(line);
            string cmd;
            ss >> cmd;

            if (cmd == "SET") {
                int x, y;
                ss >> x >> y;
                cache.set(x, y);
            } else if (cmd == "GET") {
                int x;
                ss >> x;
                int res = cache.get(x);
                output.push_back(res);
            } else {
                cout << "Неверная команда: " << cmd << endl;
            }
            }

            cout << "Результаты GET:\n";
            for (int val : output)
                cout << val << " ";
            cout << endl;
            break;
        }
    }   
}
