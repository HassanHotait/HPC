# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable and object files
TARGET = excer2.exe
OBJS = main.o io.o data.o

# Default target
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rules for object files
main.o: main.c io.h
	$(CC) $(CFLAGS) -c main.c -o main.o

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c -o data.o

# Clean target to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Disable built-in rules
.SUFFIXES:

# Phony targets
.PHONY: all clean
