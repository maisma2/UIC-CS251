CC = g++
CFLAGS = -std=c++17 -g
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = CS251Proj1P2

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	$(VALGRIND) ./$(EXECUTABLE)

clean:
	rm -f $(OBJS) $(EXECUTABLE)
