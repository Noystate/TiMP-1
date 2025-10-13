CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = cipher_program
SOURCES = main.cpp routeCipher.cpp
HEADERS = routeCipher.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
