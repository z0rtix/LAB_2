CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
ASAN_FLAGS = -fsanitize=address
LDFLAGS = 

SRCS = main.cpp utils.cpp tests.cpp menu.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = lab2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(ASAN_FLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(ASAN_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

valgrind: clean
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)