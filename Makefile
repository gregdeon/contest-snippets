# Single-file makefile for C++
# Compiler name
CC = g++
# Compiler flags
CFLAGS = -std=c++11 

# Single file target
%: %.cpp
	$(CC) $(CFLAGS) $< -o $@.out
	./$@.out
