CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = cypher

all: $(TARGET)

$(TARGET): cypther.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) cypther.o

cypther.o: cypther.cpp
	$(CXX) $(CXXFLAGS) -c cypther.cpp

clean:
	rm -f $(TARGET) *.o