CXX=g++

CPPFLAGS=-fpermissive -Wall

all: Main

Main: MathPloText.o
	$(CXX) -o MathPloText Main.cpp MathPloText.o

MathPloText.o: MathPloText.cpp MathPloText.h
	$(CXX) -c MathPloText.cpp $(CPPFLAGS)

clean:
	rm -f *.o MathPloText *~