TARGET	= mandelbrot
OBJS	= main.o mandel.o writepng.o 

OPT	= -g -O3
ISA	= 
PARA	= 

PNGWRITERPATH = pngwriter
ARCH	      = $(shell uname -p)
PNGWRTLPATH   = $(PNGWRITERPATH)/lib/$(ARCH)
PNGWRTIPATH   = $(PNGWRITERPATH)/include
PNGWRITERLIB  = $(PNGWRTLPATH)/libpngwriter.a

CC	= gcc

CCC	= g++
CXX	= g++
CXXFLAGS= -I $(PNGWRTIPATH)

CFLAGS	= $(OPT) $(ISA) $(PARA) $(XOPT)

F90C  	= gfortran
LIBS	= -L $(PNGWRTLPATH) -lpngwriter -lpng

# Default mode is 'default'
mode ?= default

# Set flags based on mode
ifeq ($(mode),openmp)
    PARA += -fopenmp
else ifeq ($(mode),default)
    # No additional flags for default mode
else
    $(error Invalid mode. Use mode=default or mode=openmp)
endif

all: $(PNGWRITERLIB) $(TARGET)

$(TARGET): $(OBJS) 
	$(CCC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(PNGWRITERLIB):
	@cd pngwriter/src && $(MAKE) -f $(MAKEFILE_LIST)

clean:
	@/bin/rm -f *.o core

realclean: clean
	@cd pngwriter/src && $(MAKE) -f $(MAKEFILE_LIST) clean
	@rm -f $(PNGWRITERLIB)
	@rm -f $(TARGET)
	@rm -f mandelbrot.png

# dependencies
#
main.o  : main.c mandel.h
mandel.o: mandel.c
writepng.o: writepng.h writepng.cc
