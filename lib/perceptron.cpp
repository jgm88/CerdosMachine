#include "perceptron.h"

Perceptron::Perceptron(){}
Perceptron::~Perceptron(){}

Perceptron::Perceptron(int size, double newAlpha)
{
	srand(time(0));
	double numRandom = (double)(rand()) / (double)RAND_MAX; 
	alpha = newAlpha;
	bias = numRandom;
	
	for (int i = 0; i < size; ++i)
	{	
    	numRandom = (double)(rand()) / (double)RAND_MAX;
		vWeights.push_back(numRandom);
	}
}

void
Perceptron::train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose)
{
	// Renicio de pesos
	srand(time(0));
	double numRandom = (double)(rand()) / (double)RAND_MAX;
	vWeights.push_back(numRandom);
	numRandom = (double)(rand()) / (double)RAND_MAX;
	vWeights.push_back(numRandom);

	int sClass;
	double open;
	double close;
	double output;
	// std::vector<double> bestWeights (vWeights.size(),0);
	// double bestbias=0;
	// int numErrors;
	// int oldNumErrors=0;
	
	while(iterations > 0)
	{
		for (int i = 0; i < numData-1; ++i)
		{
			sClass = vClass[i+1];
			open = vOpen[i];
			close = vClose[i];
			output = 1;

			if (((vWeights[0] * open + vWeights[1] * close) - bias) < 0)
		  	{
			  	output = -1;
		  	}

		  	if (output != sClass)
		  	{
		  		vWeights[0] += alpha * (sClass - output) * open;
		  		vWeights[1] += alpha * (sClass - output) * close;
		  		bias +=  alpha * (sClass - output) * (-1);
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
	if ((vWeights[0] * open + vWeights[1] * close)-bias > 0)
	{
		return 1;
	}

	return -1;
}



	// std::cout << '\n' << "TRAINPERCEPTRON TEST\n";
	// std::cout << "vWeights[0] = " << vWeights[0] << '\n';
	// std::cout << "vWeights[1] = " << vWeights[1] << '\n';
	// std::cout << "bias = " << bias << '\n';
	// std::cout << std::endl;