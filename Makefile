# Makefile для лабораторной работы 2

CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = main

# Исходные файлы
SOURCES = main.cpp \
          structures/stack.cpp \
          structures/array_triangle.cpp \
          algorithms/huffman.cpp \
          algorithms/lru.cpp \
          algorithms/rom.cpp \
          algorithms/set_connect.cpp \
          algorithms/polish.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Основная цель
all: $(TARGET)

# Компиляция основной программы
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Компиляция завершена успешно!"

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Быстрая компиляция без промежуточных файлов
fast:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "✓ Быстрая компиляция завершена!"

# Компиляция тестов
test_lru: tests/lrum.cpp algorithms/lru.cpp structures/stack.cpp
	$(CXX) $(CXXFLAGS) tests/lrum.cpp algorithms/lru.cpp -o test_lru
	@echo "✓ Тест LRU скомпилирован!"

test_polish: tests/polishm.cpp algorithms/polish.cpp structures/stack.cpp
	$(CXX) $(CXXFLAGS) tests/polishm.cpp algorithms/polish.cpp structures/stack.cpp -o test_polish
	@echo "✓ Тест Polish скомпилирован!"

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET) test_lru test_polish
	rm -f structures/*.o algorithms/*.o tests/*.o
	@echo "✓ Очистка завершена!"

# Очистка всех бинарников
cleanall: clean
	rm -f a.out a_t hf hfm lru lrum po pol polish romm set set_connect core.*
	@echo "✓ Полная очистка завершена!"

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Помощь
help:
	@echo "Доступные команды:"
	@echo "  make          - Компиляция основной программы"
	@echo "  make fast     - Быстрая компиляция без .o файлов"
	@echo "  make test_lru - Компиляция теста LRU"
	@echo "  make test_polish - Компиляция теста Polish"
	@echo "  make clean    - Удаление объектных файлов и бинарников"
	@echo "  make cleanall - Полная очистка всех файлов"
	@echo "  make run      - Компиляция и запуск программы"
	@echo "  make help     - Показать эту справку"

.PHONY: all fast clean cleanall run help test_lru test_polish
