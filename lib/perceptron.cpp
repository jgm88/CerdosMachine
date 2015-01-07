#include "perceptron.h"

Perceptron::Perceptron(){}
Perceptron::~Perceptron(){}

Perceptron::Perceptron(int size, double newAlpha)
{
	srand(time(0));
	alpha = newAlpha;
	double numRandom = (double)(rand()) / (double)RAND_MAX; 
	threshold = numRandom;
	
	for (int i = 0; i < size; ++i)
	{	
    	numRandom = (double)(rand()) / (double)RAND_MAX;
		vWeights.push_back(numRandom);
	}
}

void
Perceptron::trainPerceptron(int iterations, int numData, int vClass[], double vOpen[], double vClose[])
{
	int sClass;
	double open;
	double close;
	double output;

	while(iterations > 0)
	{
		for (int i = 0; i < numData; ++i)
		{
			sClass = vClass[i];
			open = vOpen[i];
			close = vClose[i];
			output = 1;

			if (((vWeights[0] * open + vWeights[1] * close) - threshold) < 0)
		  	{
			  	output = 0;
		  	}

		  	if (output != sClass)
		  	{
		  		vWeights[0] += alpha * (sClass - output) * open / 2;
		  		vWeights[1] += alpha * (sClass - output) * close / 2;
		  		threshold +=  alpha * (sClass - output) * (-1) / 2;
		  	}
		}	
		--iterations;

	}
	//PRUEBAS
	std::cout << std::endl;
	std::cout << "vWeights[0] = " << vWeights[0] << '\n';
	std::cout << "vWeights[1] = " << vWeights[1] << '\n';
	std::cout << "threshold = " << threshold << '\n';
	std::cout << std::endl;
}

void 
Perceptron::setAlpha(double newAlpha)
{
	alpha = newAlpha;
}

int 
Perceptron::validate(double open, double close)
{
	if (((vWeights[0] * open + vWeights[1] * close) - threshold) < 0)
	{
		return 0;
	}

	return 1;
}