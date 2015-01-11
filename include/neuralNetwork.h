#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

class NeuralNetwork
{
public:
    NeuralNetwork();
    ~NeuralNetwork();
    NeuralNetwork(double newEta, int inputs);

    void train(int iterations, int numData, int vClass[], double vOpen[], double vClose[]);
    double probability(double open, double close);
    int validate(double open, double close);
    void setEta(double newEta);
private:
    std::vector<double> vWeights;
    double eta;

};
#endif