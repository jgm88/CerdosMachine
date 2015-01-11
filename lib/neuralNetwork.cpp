#include "../include/neuralNetwork.h"
#include "../include/perceptron.h"

/*
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
*/

/**
MI PARTE
**/

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for(unsigned c = 0; c < numOutputs; ++ c)
	{
		m_ouputWeights.push_back(Connection());
		m_ouputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}

void Neuron::feedFordward(const Layer &prevLayer)
{
	double sum = 0.0;

	for(unsigned n = 0; n < prevLayer.size(); ++ n)
	{
		sum += prevLayer[n].getOuputVal() * prevLayer[n].m_ouputWeights[m_myIndex].weight;
	}

	m_ouputVal = Neuron::transferFunction(sum);
}

static double Neuron::transferFunction(double x)
{
	return tanh(x);
}
 
static double Neuron::transferFunctionDerivative(double x)
{
	return 1.0 - x * x;
}

neuralNetwork::neuralNetwork(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();

	for(unsigned layerNum = 0; layerNum < numLayers; ++ layerNum)
	{
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++ neuronNum);
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			cout << "Made a Neuron" << endl; 
		}
	}
}

void neuralNetwork::feedFordward(const vector<double> &inputVals)
{
	assert(inputVals.size() == m_layers[0].size() - 1);

	for (unsigned i = 0; i < inputVals.size(); ++ i)
	{
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	// Fordward Propagation
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++ layerNum)
	{
		Layer &prevLayer = m_layers[layerNum - 1];

		for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++ n)
		{
			m_layers[layerNum][n].feedFordward(prevLayer);
		}
	}
}

https://www.youtube.com/watch?v=KkwX7FkLfug
Minuto 45
void neuralNetwork::backProp(const vector<double> &targetVals)
{

}

void neuralNetwork::getResults(vector<double> &resultsVals) const
{

}

int main()
{
	vector<unsigned> topology;
	
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);

	vector<double> inputVals;
	vector<double> targetVals;
	vector<double> resultsVals;

	neuralNetwork myNet(topology);

	myNet.feedFordward(inputVals);
	myNet.backProp(targetVals);
	myNet.getResults(resultsVals);
}






