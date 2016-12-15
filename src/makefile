CXX=g++

CPPFLAGS=-g 

all: Main

Main: MathPloText.o
	$(CXX) -o MathPloText Main.cpp MathPloText.o

MathPloText.o: MathPloText.cpp MathPloText.hpp
	$(CXX) -c MathPloText.cpp $(CPPFLAGS)

clean:
	rm -f *.o MathPloText *~