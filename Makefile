CXX=g++
CXXFLAGS=-O3 -march=native

all: ASMT4

ASMT4: ASMT4_polynomial.cpp polynomial.h root.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: all
