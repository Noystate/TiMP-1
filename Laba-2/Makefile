CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lUnitTest++

TARGET = test_gronsfeld
SOURCES = test_modAlphaCipher.cpp modAlphaCipher.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all test clean
