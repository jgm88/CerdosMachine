.PHONY= clean

CC=g++
OPTIONS=-DARMA_DONT_USE_WRAPPER -lblas -llapack
DEBUG= #-D DEBUG
CFLAGS= -std=c++11 -Wall -g -O3 
BOTFLAGS = -std=c++11
LIBDIR=lib
INCLUDEDIR=include
_OBJ= perceptron.o linearRegression.o logisticRegression.o multiLinearRegression.o crossValidation.o neuralNetwork.o  
# bot.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: machineLearning

machineLearning:    main.cpp $(OBJ)
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o cpcr2Machine

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<

preprocesador:
	$(CC) $(CFLAGS) preprocesador.cpp -o preprocesador
	$(CC) $(CFLAGS) preprocesadorFran.cpp -o preprocesadorFran

bot:
	$(CC) $(CFLAGS) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) bot.cpp $(OBJ) -o botCpcr2

clean:
	rm -f $(OBJ) 
	rm cpcr2Machine
	rm plot/*.data
	rm botCpcr2
clean-p:
	rm preprocesador
	rm preprocesadorFran