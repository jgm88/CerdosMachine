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
	// std::vector<double> bestWeights;
	// double bestThreshold=0;
	// int numErrors;
	// int oldNumErrors=numData;
	
	while(iterations > 0)
	{
		// numErrors= 0;
		for (int i = 0; i < numData-1; ++i)
		{
			sClass = vClass[i+1];
			open = vOpen[i];
			close = vClose[i];
			output = 1;

			if (((vWeights[0] * open + vWeights[1] * close) -threshold) < 0)
		  	{
			  	output = -1;
		  	}

		  	if (output != sClass)
		  	{
		  		vWeights[0] += alpha * (sClass - output) * open;
		  		vWeights[1] += alpha * (sClass - output) * close;
		  		threshold +=  alpha * (sClass - output) * (-1);
		  		// ++numErrors;
		  	}
		}	
		// for(int i=0; i< numData-1; ++i)
		// {
		// 	if(validate(vOpen[i],vClose[i]) != vClass[i+1])
		// 		++numErrors;
		// }
		// Fallo en la comprobacion de los errores
		// La recta actual tiene q mejorar la recta anteriorx
		// if(oldNumErrors > numErrors)
		// {
		// 	std::cout << "Errores: Old "<< oldNumErrors << " new " << numErrors<< std::endl;
		// 	bestWeights = vWeights;
		// 	bestThreshold= threshold;
		// 	oldNumErrors= numErrors;
		// }
		--iterations;

	}
	//PRUEBAS
	std::cout << '\n' << "TRAINPERCEPTRON TEST\n";
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
	if ((vWeights[0] * open + vWeights[1] * close)-threshold > 0)
	{
		return 1;
	}

	return -1;
}