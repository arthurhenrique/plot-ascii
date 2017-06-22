CXX=g++

CPPFLAGS=-g -std=c++11

all: Main

Main: MathPloText.o
	$(CXX) $(CPPFLAGS) -o MathPloText Main.cpp MathPloText.o 

MathPloText.o: MathPloText.cpp MathPloText.hpp
	$(CXX) $(CPPFLAGS) -c MathPloText.cpp 

clean:
	rm -f *.o MathPloText *~
