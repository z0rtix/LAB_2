CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRCS = main.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = lab2

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

.PHONY: all clean rebuild run