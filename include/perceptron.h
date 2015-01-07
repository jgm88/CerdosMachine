#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <isotream>


class perceptron
{
public:
    perceptron();
    ~perceptron();

    trainPerceptron(float treshold);

private:

    //pesos del perceptron
    std::vector<double> vWeights;
    //entradas del perceptron 
    std::vector<double> vInputs;
    //salida
    int y;

};


#endif