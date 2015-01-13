.PHONY= clean

CC=g++
OPTIONS=-DARMA_DONT_USE_WRAPPER -lblas -llapack
DEBUG= #-D DEBUG
CFLAGS= -std=c++11 -Wall -g -O3 
LIBDIR=lib
INCLUDEDIR=include
_OBJ= perceptron.o linearRegression.o logisticRegression.o multiLinearRegression.o crossValidation.o neuralNetwork.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: machineLearning

machineLearning:    main.cpp $(OBJ)
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o cpcr2Machine

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

preprocesador:
	$(CC) $(CFLAGS) preprocesador.cpp -o preprocesador
	$(CC) $(CFLAGS) preprocesadorFran.cpp -o preprocesadorFran

clean:
	rm -f $(OBJ) 
	rm cpcr2Machine
	rm plot/*.data
clean-p:
	rm preprocesador
	rm preprocesadorFran