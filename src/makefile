CXX=g++

CPPFLAGS=-g -std=c++11

all: Main

Main: MathPloText.o MathPloTextParser.o
	$(CXX) $(CPPFLAGS) -o MathPloText Main.cpp MathPloText.o MathPloTextParser.o

MathPloText.o: MathPloText.cpp MathPloText.hpp MathPloTextFunction.hpp
	$(CXX) $(CPPFLAGS) -c MathPloText.cpp

MathPloTextParser.o: MathPloTextParser.cpp MathPloTextParser.hpp MathPloTextFunction.hpp
	$(CXX) $(CPPFLAGS) -c MathPloTextParser.cpp

clean:
	rm -f *.o MathPloText *~
