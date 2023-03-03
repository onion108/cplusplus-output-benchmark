CXX = g++
CXXFLAGS = -O2 -Wall -std=c++14

.PHONY: all
all: dist/main

test: all
	dist/main

dist:
	@mkdir dist

dist/main:dist src/main.cc
	$(CXX) $(CXXFLAGS) -o dist/main src/main.cc



