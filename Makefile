CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -g
LDFLAGS = -lcryptopp
TARGET = cypher

all: $(TARGET)

$(TARGET): cypther.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) cypther.o $(LDFLAGS)

cypther.o: cypther.cpp
	$(CXX) $(CXXFLAGS) -c cypther.cpp

# crypt.o: crypt.cpp crypt.h
# 	$(CXX) $(CXXFLAGS) -c crypt.cpp

clean:
	rm -f $(TARGET) *.o