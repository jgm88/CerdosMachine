.PHONY= doc clean

GCC=g++
OPTIONS= -g
DEBUG= #-D DEBUG 
CFLAGS= -std=c++11

LIBDIR=lib
INCLUDEDIR=include
MAINFILE=main

_OBJ= perceptron.o 
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

main:    main.cpp $(OBJ)
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

doc:
	doxygen

clean:
	rm -f $(OBJ) 
