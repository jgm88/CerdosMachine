#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;

/*class NeuralNetwork
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

};*/

struct Connection
{
    double weight;
    double deltaWeight;    
};

/** class neuron **/
class Neuron {
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputVal(double val) {m_outputVal = val;}
    void getOutputVal(void) const {return m_outputVal;}
    void feedFordward(const Layer &prevLayer);
private:
    static double transferFunction(double x);
    static double transferFunctionDerivative(double x);
    unsigned m_myIndex;  
    double m_outputVal;
    vector<Connection> m_ouputWeights;
    static double randomWeight(void) { return rand() / double(RAND_MAX);}
};

typedef vector<Neuron> Layer;


/** class neural network **/
class neuralNetwork
{
public:
    neuralNetwork(const vector<unsigned> &topology);
    void feedFordward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals);
    void getResults(vector<double> &resultsVals) const;
private:
    vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
};
#endif