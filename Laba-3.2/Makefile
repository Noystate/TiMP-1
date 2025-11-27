CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LIBS = -lUnitTest++

TARGET = routecipher_test
SOURCES = main.cpp routecipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

main.o: main.cpp routecipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

routecipher.o: routecipher.cpp routecipher.h
	$(CXX) $(CXXFLAGS) -c routecipher.cpp -o routecipher.o

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test
