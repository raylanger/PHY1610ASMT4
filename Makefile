CXX=g++
CXXFLAGS=-O3 -march=native
LDLIBS=-lgsl -lgslcblas

all: ASMT4

ASMT4: polynomial.o main.o multivariate.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

multivariate.o: ASMT4_multivariate.cpp multivariate.h root.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

polynomial.o: ASMT4_polynomial.cpp polynomial.h root.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

main.o: ASMT4_main.cpp polynomial.h root.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) polynomial.o main.o multivariate.o

.PHONY: all clean
