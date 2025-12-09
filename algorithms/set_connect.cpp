#include "set_connect.h"
#include <fstream>

Set::Set() {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table.push_back(DoublyLinkedList<int>());
}

int Set::hashFunction(int key) const {
    int h = key % TABLE_SIZE;
    return (h < 0) ? -h : h;
}

void Set::add(int value) {
    int index = hashFunction(value);
    if (!table[index].search(value))
        table[index].addTail(value);
}

bool Set::contains(int value) const {
    int index = hashFunction(value);
    return table[index].search(value);
}

int Set::intersectionCount(const Set& other){
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Array<int> elems;
        table[i].toArray(elems); 
        for (int k = 0; k < elems.size(); ++k) {
            if (other.contains(elems[k]))
                count++;
        }
    }
    return count;
}

void Set::print(){
    cout << "{ ";
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Array<int> elems;
        table[i].toArray(elems);
        for (int k = 0; k < elems.size(); ++k)
            cout << elems[k] << " ";
    }
    cout << "}";
}
void Set::remove(int value) {
    int index = hashFunction(value);
    table[index].deleteValue(value);
}

void Set::loadFromFile(const string& path) {
    ifstream fin(path);
    if (!fin) {
        cerr << "Файл не найден, создаётся новый: " << path << endl;
        return;
    }
    int value;
    while (fin >> value) {
        add(value);
    }
    fin.close();
}

void Set::saveToFile(const string& path){
    ofstream fout(path, ios::trunc);
    for (int i = 0; i < table.size(); ++i) {
        auto cur = table[i].head;
        while (cur) {
            fout << cur->value << "\n";
            cur = cur->next;
        }
    }
    fout.close();
}

void findMaxIntersection(Array<Set>& sets) {
    int n = sets.size();
    int maxCount = -1;
    int setA = -1, setB = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int common = sets[i].intersectionCount(sets[j]);
            if (common > maxCount) {
                maxCount = common;
                setA = i;
                setB = j;
            }
        }
    }

    if (setA == -1) {
        cout << "Нет множеств для сравнения.\n";
        return;
    }

    cout << "Максимальное пересечение между множествами #"
         << setA + 1 << " и #" << setB + 1 << endl;

    cout << "Множество #" << setA + 1 << " = ";
    sets[setA].print();
    cout << endl;

    cout << "Множество #" << setB + 1 << " = ";
    sets[setB].print();
    cout << endl;

    cout << "Количество общих элементов: " << maxCount << endl;
}