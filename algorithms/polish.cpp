#include "polish.h"
#include "../structures/stack.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

double evaluatePostfix(const string& expr) {
    Stack st;

    for (size_t i = 0; i < expr.length(); ++i) {
        char token = expr[i];

        if (isspace(token)) continue;

        if (isdigit(token)) {
            int num = token - '0';
            st.push(num);
        } else {
            if (st.isEmpty()) {
                cout << "Ошибка: недостаточно операндов для операции '" << token << "'!" << endl;
                return 0;
            }
            int b = st.pop();
            
            if (st.isEmpty()) {
                cout << "Ошибка: недостаточно операндов для операции '" << token << "'!" << endl;
                return 0;
            }
            int a = st.pop();
            int result = 0; 

            switch (token) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        cout << "Ошибка: деление на ноль!" << endl;
                        return 0;
                    }
                    result = a / b; 
                    break;
                default:
                    cout << "Ошибка: неизвестный оператор " << token << endl;
                    return 0;
            }

            st.push(result);
        }
    }

    if (st.isEmpty()) {
        cout << "Ошибка: пустое выражение!" << endl;
        return 0;
    }
    
    int finalResult = st.pop();
    
    if (!st.isEmpty()) {
        cout << "Предупреждение: в стеке остались неиспользованные операнды!" << endl;
    }
    
    return finalResult;
}
