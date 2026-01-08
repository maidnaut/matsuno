CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinc $(shell pkg-config --cflags raylib)
LDFLAGS := $(shell pkg-config --libs raylib) -lm

TARGET := matsuno

SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
	@rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)