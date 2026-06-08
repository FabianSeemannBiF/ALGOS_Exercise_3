CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC = src/main.cpp src/graph_parser.cpp src/dijkstra.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = find_path

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f src/*.o $(TARGET)