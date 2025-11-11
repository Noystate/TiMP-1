# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Цели
TARGET = gronsfeld_cipher
TEST_TARGET = test_modAlphaCipher

# Исходные файлы
MAIN_SRCS = main.cpp modAlphaCipher.cpp
TEST_SRCS = test_modAlphaCipher.cpp modAlphaCipher.cpp

# Объектные файлы
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Сборка основной программы
$(TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Сборка тестовой программы
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция .cpp файлов в .o файлы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Отладочная сборка
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET) $(TEST_TARGET)

# Релизная сборка
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

# Установка
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all      - сборка основной программы"
	@echo "  test     - сборка и запуск тестов"
	@echo "  debug    - отладочная сборка"
	@echo "  release  - релизная сборка"
	@echo "  clean    - очистка сборочных файлов"
	@echo "  install  - установка программы"
	@echo "  help     - эта справка"

# Зависимости
main.o: modAlphaCipher.h
modAlphaCipher.o: modAlphaCipher.h
test_modAlphaCipher.o: modAlphaCipher.h

.PHONY: all test debug release clean install help
