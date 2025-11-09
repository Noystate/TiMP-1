# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lUnitTest++

# Имена файлов
TARGET = test_routecipher
SOURCES = test_routeCipher.cpp routeCipher.cpp

# Основная цель
all: $(TARGET)

# Компиляция тестов
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Запуск тестов
test: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(TARGET) *.o

# Указываем что это phony targets
.PHONY: all test clean
