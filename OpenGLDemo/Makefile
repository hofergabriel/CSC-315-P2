# Makefile for OpenGL/GLUT programs.

# Author: John M. Weiss, Ph.D.
# Class:  CSC 315 Data Structures & Algorithms
# Date:   Spring 2018

# Usage:  make target1 target2 ...

# GNU C/C++ compiler and linker:
LINK = g++

# Preprocessor and compiler flags (turn on warnings, optimization and debugging):
# CPPFLAGS = <preprocessor flags go here>
CFLAGS = -Wall -O -g -fmax-errors=5
CXXFLAGS = $(CFLAGS) -std=c++11

# OpenGL/Mesa libraries for Linux
GL_LIBS = -lglut -lGLU -lGL
# add in POSIX threads library, to prevent driver issues in Linux Lab
GL_LIBS += -lpthread

# Targets
# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:	OpenGLDemo

# source and object files
SRC = OpenGLDemo.cpp callbacks.cpp globals.cpp graphics.cpp
OBJ = $(SRC:.cpp=.o)

OpenGLDemo:	$(OBJ)
	$(LINK) -o $@ $^ $(GL_LIBS)

clean:
	rm -f *.o ~* core a.out

