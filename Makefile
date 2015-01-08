.PHONY= clean

CC=g++
OPTIONS= -g 
DEBUG= #-D DEBUG
CFLAGS= -std=c++11 -Wall
CGNUPLOT = -lboost_iostreams -lboost_system -lboost_filesystem
LIBDIR=lib
INCLUDEDIR=include
_OBJ= *.o 
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: machineLearning

machineLearning:    main.cpp $(OBJ)
	$(CC) $(CFLAGS) $(CGNUPLOT) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) $(CGNUPLOT) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) 