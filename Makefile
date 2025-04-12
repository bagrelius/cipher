CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -g
LDFLAGS = -lcryptopp
TARGET = cipher

all: $(TARGET)

$(TARGET): cipher.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) cipher.o $(LDFLAGS)

cipher.o: cipher.cpp
	$(CXX) $(CXXFLAGS) -c cipher.cpp

# crypt.o: crypt.cpp crypt.h
# 	$(CXX) $(CXXFLAGS) -c crypt.cpp

clean:
	rm -f $(TARGET) *.o