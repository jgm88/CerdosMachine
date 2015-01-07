#include "perceptron.h"

Perceptron::Perceptron(){}
Perceptron::~Perceptron(){}

Perceptron::Perceptron(int size, double initWeight, double newAlpha)
{
	alpha = newAlpha;
	for (int i = 0; i < size; ++i)
	{	
		vWeights.push_back(initWeight);
	}
}

void
Perceptron::trainPerceptron(float threshold, int iterations, int numData, int vClass[], double vOpen[], double vClose[])
{
	int sClass;
	double open;
	double close;
	double output;

	while(iterations > 0){
		for (int i = 0; i < numData; ++i)
		{
			sClass = vClass[i];
			open = vOpen[i];
			close = vClose[i];
			output = 1;

			if ((vWeights[0] * open + vWeights[1] * close) < 0)
		  	{
			  	output = 0;
		  	}

		  	if (output != sClass)
		  	{
		  		vWeights[0] += alpha * (sClass - output) * open / 2;
		  		vWeights[1] += alpha * (sClass - output) * close / 2; 
		  	}
		}	
		--iterations;
	}
}

void 
Perceptron::setAlpha(double newAlpha)
{
	alpha = newAlpha;
}

int 
Perceptron::validate(double open, double close)
{
	if ((vWeights[0] * open + vWeights[1] * close) < 0)
	{
		return 0;
	}

	return 1;
}