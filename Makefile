CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRCS = main.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = lab2

.PHONY: all clean rebuild run valgrind test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

test: run

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# если нужен отладчик
debug: $(TARGET)
	gdb ./$(TARGET)