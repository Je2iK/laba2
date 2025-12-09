#!/bin/bash
# Тестовый скрипт для проверки всех функций программы

echo "=== ТЕСТ 1: Postfix ==="
echo -e "1\n53+" | ./main
echo ""

echo "=== ТЕСТ 3: Set_connect ==="
echo "3" | ./main
echo ""

echo "=== ТЕСТ 4: Array_triangle ==="
echo -e "4\n3\n3 2\n2 3\n1 5" | ./main
echo ""

echo "=== ТЕСТ 5: Huffman ==="
echo -e "5\nhello world" | ./main
echo ""

echo "=== ТЕСТ 6: Roman ==="
echo -e "6\n1994" | ./main
echo ""

echo "=== ТЕСТ 7: LRU Cache ==="
echo -e "7\n2\n4\nSET 1 10\nSET 2 20\nGET 1\nSET 3 30" | ./main
echo ""

echo "=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ ==="
