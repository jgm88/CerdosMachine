#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <iostream>
#include <vector>

class Perceptron
{
public:
    Perceptron();
    Perceptron(int size, double initWeight, double alpha);
    ~Perceptron();

    void trainPerceptron(float threshold, int iterations, int numData, int vClass[], double vOpen[], double vClose[]);
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

};


#endif