CXX=g++
CXXFLAGS=-O3 -march=native
LDLIBS=-lgsl -lgslcblas

all: ASMT4

ASMT4: polynomial.o main.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

polynomial.o: ASMT4_polynomial.cpp polynomial.h root.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

main.o: ASMT4_main.cpp polynomial.h root.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: all
