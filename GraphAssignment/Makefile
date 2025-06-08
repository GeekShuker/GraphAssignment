# meirshuker159@gmail.com
# Makefile for Graph Assignment

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -IInclude -IInclude/data_structures
SRC = src/Graph.cpp src/Algorithms.cpp \
      src/data_structures/Queue.cpp \
      src/data_structures/PriorityQueue.cpp \
      src/data_structures/UnionFind.cpp

MAIN = main.cpp
TEST = Test/test_graph.cpp


# Build the main executable
Main: $(MAIN) $(SRC)
	$(CXX) $(CXXFLAGS) -o Main $(MAIN) $(SRC)
	./Main

# Build and run unit tests
test: $(TEST) $(SRC)
	$(CXX) $(CXXFLAGS) -o test $(TEST) $(SRC)
	./test

# Check for memory leaks
valgrind: Main
	valgrind ./Main

# Clean build artifacts
clean:
	rm -f Main test valgrind
