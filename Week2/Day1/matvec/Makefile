# Compiler and common settings
CC = gcc
CFLAGS_COMMON =  -O2
LDFLAGS_COMMON =

# Targets
TARGET = matvec
SRCS = main.c

# Default mode (default if not specified)
mode ?= default

# Flags for OpenMP
CFLAGS_OPENMP = $(CFLAGS_COMMON) -fopenmp
LDFLAGS_OPENMP = -fopenmp

# Flags for Autopar
CFLAGS_AUTOPAR = $(CFLAGS_COMMON) -ftree-parallelize-loops=4 -ffast-math #-ftree-vectorize -ftree-slp-vectorize -funroll-loops
LDFLAGS_AUTOPAR =

# Select flags based on mode
ifeq ($(mode), openmp)
    CFLAGS = $(CFLAGS_OPENMP)
    LDFLAGS = $(LDFLAGS_OPENMP)
else ifeq ($(mode), autopar)
    CFLAGS = $(CFLAGS_AUTOPAR)
    LDFLAGS = $(LDFLAGS_AUTOPAR)
else ifeq ($(mode), default)
    CFLAGS = $(CFLAGS_COMMON)
    LDFLAGS = $(LDFLAGS_COMMON)
else
    $(error Invalid mode specified. Use 'mode=openmp', 'mode=autopar', or 'mode=default')
endif

# Default target
all: $(TARGET)

# Compile the target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGET)
