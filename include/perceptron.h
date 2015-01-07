#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <isotream>


class perceptron
{
public:
    perceptron();
    ~perceptron();

private:

    //pesos del perceptron
    std::vector<double> vW;
    //entradas del perceptron 
    std::vector<double> vX;
    //salida
    int y;

};


#endif