#include "neuralNetwork.h"

NeuralNetwork::NeuralNetwork(){}
NeuralNetwork::~NeuralNetwork(){}
NeuralNetwork::NeuralNetwork(double newEta, int inputs)
{
	vWeights = std::vector<double> (inputs, 0);
	eta = newEta;
}

void 
NeuralNetwork::train(int iterations, int numData, int vClass[], double vOpen[], double vClose[])
{
	int sClass;
	double open;
	double close;
	double gradient;
	// int contador = 20;
	while(iterations > 0)
	{
		for (int i = 0; i < numData-1; ++i)
		{
			sClass = vClass[i+1];
			open = vOpen[i];
			close = vClose[i];

			gradient += (sClass * open) / (1 + exp(sClass * vWeights[0] * open));
			gradient += (sClass * close) / (1 + exp(sClass * vWeights[1] * close));
			gradient /= -1/ vWeights.size();
		}
		vWeights[0] -= eta * gradient;
		vWeights[1] -= eta * gradient;
		gradient = 0;
		--iterations;
	}
}
void 
NeuralNetwork::setEta(double newEta)
{
	eta = newEta;
}
double 
NeuralNetwork::probability(double open, double close)
{
	return (1 / (1 + exp((-1) * (vWeights[0] * open) + (vWeights[1] * close))));
}
int 
NeuralNetwork::validate(double open, double close)
{
	// std::cout << "Probabilidad Regresion Logistica: ";
	// std::cout << probability(open,close) <<'\n';
	if(probability(open, close) >= 0)
		return 1;

	return -1;
}