#include "neuralNetwork.h"

void Neuron::updateInputWeights(Layer &prevLayer)
{
    for (unsigned n = 0; n < prevLayer.size(); ++n) 
    {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient + alpha * oldDeltaWeight;

        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
    }
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0.0;

    for (unsigned n = 0; n < nextLayer.size() - 1; ++n) 
    {
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
    }

    return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVal)
{
    double delta = targetVal - m_outputVal;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{
    return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
    return 1.0 - x * x;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;

    for (unsigned n = 0; n < prevLayer.size(); ++n) 
    {
        sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex, double newEta, double newAlpha)
{
    for (unsigned c = 0; c < numOutputs; ++c) 
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }

    m_myIndex = myIndex;

    eta = newEta;
    alpha = newAlpha;
}

void NeuralNetwork::getResults(vector<double> &resultVals) const
{
    resultVals.clear();

    for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) 
    {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}

void NeuralNetwork::backProp(const vector<double> &targetVals)
{
    Layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) 
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }

    m_error /= outputLayer.size() - 1; 
    m_error = sqrt(m_error); 

    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) 
    {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) 
    {
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n) 
        {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) 
    {
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) 
        {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void NeuralNetwork::feedForward(const vector<double> &inputVals)
{
    assert(inputVals.size() == m_layers[0].size() - 1);

    for (unsigned i = 0; i < inputVals.size(); ++i) 
    {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) 
    {
        Layer &prevLayer = m_layers[layerNum - 1];

        for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) 
        {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

NeuralNetwork::NeuralNetwork(double newAlpha)
{
    topology.push_back(2);
    topology.push_back(1);

    m_recentAverageSmoothingFactor = 100.0;
    unsigned numLayers = topology.size();

    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) 
    {
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) 
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum, 0.15, newAlpha));
        }

        m_layers.back().back().setOutputVal(1.0);
    }
}

void NeuralNetwork::train(int iterations, int numData, vector<int> vClass, vector<double> vOpen, vector<double> vClose)
{
    vector<double> resultVals;
    vector<double> entryVals;
    vector<double> expectedVals;

    while (iterations > 0) 
    {
        for(int i = 0; i < numData - 1; ++i)
        {
            entryVals.push_back(vOpen[i]);
            entryVals.push_back(vClose[i]);

            expectedVals.push_back(vOpen[i + 1]);
            expectedVals.push_back(vClose[i + 1]);

            feedForward(entryVals);
            getResults(resultVals);
            backProp(expectedVals);
            entryVals.clear();
        }

        --iterations;
    }
}   

int NeuralNetwork::validate(double open, double close)
{
    vector<double> resultVals;
    vector<double> entryVals;
    entryVals.push_back(open);
    entryVals.push_back(close);

    feedForward(entryVals);

    getResults(resultVals);

    if(resultVals[0] > resultVals[1])
    {
        return 1;
    }

    return -1;
}
