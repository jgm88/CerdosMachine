.PHONY= clean

CC=g++
OPTIONS= -g -O2 -DARMA_DONT_USE_WRAPPER -lblas -llapack
DEBUG= #-D DEBUG
CFLAGS= -std=c++11 -Wall
LIBDIR=lib
INCLUDEDIR=include
_OBJ= perceptron.o linearRegression.o logisticRegression.o multiLinearRegression.o crossValidation.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: machineLearning

machineLearning:    main.cpp $(OBJ)
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o cpcr2Machine

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

clean:
	rm -f $(OBJ) 
	rm cpcr2Machine