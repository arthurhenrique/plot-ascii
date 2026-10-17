CXX=g++

CPPFLAGS=-g -std=c++11

SRC=src

#every function of the README gallery, read from tools/gallery.txt
FUNCTIONS=$(shell awk -F'|' '!/^\#/ && NF == 5 {print $$1}' tools/gallery.txt)

.PHONY: all clean list gallery $(FUNCTIONS)

all: MathPloText

MathPloText: $(SRC)/Main.cpp $(SRC)/MathPloText.o $(SRC)/MathPloTextParser.o
	$(CXX) $(CPPFLAGS) -o MathPloText $(SRC)/Main.cpp $(SRC)/MathPloText.o $(SRC)/MathPloTextParser.o

$(SRC)/MathPloText.o: $(SRC)/MathPloText.cpp $(SRC)/MathPloText.hpp $(SRC)/MathPloTextStruct.hpp $(SRC)/MathPloTextFunction.hpp
	$(CXX) $(CPPFLAGS) -c $(SRC)/MathPloText.cpp -o $(SRC)/MathPloText.o

$(SRC)/MathPloTextParser.o: $(SRC)/MathPloTextParser.cpp $(SRC)/MathPloTextParser.hpp $(SRC)/MathPloTextFunction.hpp $(SRC)/MathPloTextArsenal.hpp $(SRC)/MathPloTextFluid.hpp
	$(CXX) $(CPPFLAGS) -c $(SRC)/MathPloTextParser.cpp -o $(SRC)/MathPloTextParser.o

#make heart, make burgers, ...: runs that function as in the README
$(FUNCTIONS): MathPloText
	@eval "./MathPloText $$(awk -F'|' -v name=$@ '$$1 == name { gsub(/;;/, "\" \"", $$5); print $$4 " \"" $$5 "\"" }' tools/gallery.txt)"

#every function you can run, by category
list:
	@awk -F'|' '/^# / { sub(/^# /, ""); print "\n" $$1 } !/^#/ && NF == 5 { printf "  make %-14s %s\n", $$1, $$2 }' tools/gallery.txt

#gifs and README gallery (needs python3 and Pillow)
gallery: MathPloText
	python3 tools/gallery.py

clean:
	rm -f $(SRC)/*.o MathPloText *~
