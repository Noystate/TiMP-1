# Компилятор и флаги компиляции
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LIBS = -lUnitTest++

# Имена файлов (ЗАМЕНИТЕ НА СВОИ!)
TARGET = cipher_test
SOURCES = main.cpp modAlphaCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Основная цель - линковка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Компиляция объектных файлов
main.o: main.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp -o modAlphaCipher.o

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Запуск тестов
test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test
