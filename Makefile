CXX = g++
CXXFLAGS = -Wall -g -std=c++17
INCLUDES = -I.
SRCS = BST.cpp Date.cpp Main.cpp Node.cpp Product.cpp Store.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = shop

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS) $(EXEC) a.out

.PHONY: all clean

