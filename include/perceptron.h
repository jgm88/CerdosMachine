#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <iostream>
#include <vector>
#include <stdlib.h>

class Perceptron
{
public:
    Perceptron();
    Perceptron(int size, double alpha);
    ~Perceptron();
    void train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
    void setAlpha(double newAlpha);
    int validate(double open, double close);

private:

    //pesos del perceptron
    std::vector<double> vWeights;
    	//entradas del perceptron 
    	//std::vector<double> vInputs;
    //salida
    int y;
    //valor constante aprendizaje learning rate 0<alpha<1
    double alpha;
    double bias;

};


#endif