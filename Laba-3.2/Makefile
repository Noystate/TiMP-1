# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -lUnitTest++

# Исходные файлы
SOURCES = routeCipher.cpp test_routeCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Исполняемые файлы
TEST_EXEC = test_routecipher
MAIN_EXEC = main

# Цели по умолчанию
all: $(TEST_EXEC) $(MAIN_EXEC)

# Сборка тестов
$(TEST_EXEC): test_routeCipher.o routeCipher.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# Сборка основной программы
$(MAIN_EXEC): main.o routeCipher.o
	$(CXX) -o $@ $^

# Правило для объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск тестов
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Запуск основной программы
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Очистка
clean:
	rm -f *.o $(TEST_EXEC) $(MAIN_EXEC)

# Пересборка
rebuild: clean all

.PHONY: all test run clean rebuild
