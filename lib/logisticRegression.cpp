#include "logisticRegression.h"

LogisticRegression::LogisticRegression(){}
LogisticRegression::~LogisticRegression(){}
LogisticRegression::LogisticRegression(double newEta, int inputs)
{
	vWeights = std::vector<double> (inputs, 0.03);
	eta = newEta;
}

void 
LogisticRegression::train(int iterations, int numData, int vClass[], double vOpen[], double vClose[])
{
	int sClass;
	double pesos0=0, pesos1=0;
	double cost, oldCost=99;
	double minError=0;
	bool isMinErr= false;

	while(iterations > 0  )
	{
		cost =calculateCost(numData,vClass,vOpen,vClose);
		// std::cout << "coste Iteracion "<<iterations <<" : " << cost<< std::endl;
		for (int i = 0; i < numData-1; ++i)
		{
			// la clase que entre esta definida con -1 y 1
			// hacemos la siguiente operaciones para definirla entre 0 y 1
			sClass = (vClass[i+1]+1)/2; 

			pesos0 += (probability(vOpen[i],vClose[i])- sClass)*vOpen[i];
			pesos1 += (probability(vOpen[i],vClose[i])- sClass)*vClose[i];
			// gradient += (sClass * open) / (1 + exp(sClass * vWeights[0] * open));
			// gradient += (sClass * close) / (1 + exp(sClass * vWeights[1] * close));
		}
		oldCost= cost;
		vWeights[0] -= eta*pesos0;
		vWeights[1] -= eta*pesos1;
		//  	gradient *= -1/ (numData-1);
		// vWeights[0] -= eta * gradient;
		// vWeights[1] -= eta * gradient;
		--iterations;
	}

	std::cout << "pesos Finales: "<< vWeights[0]<< " "<< vWeights[1]<< std::endl;
}

double
LogisticRegression::calculateCost(int numData, int vClass[], double vOpen[], double vClose[])
{
	double cost = 0, dClass;
	for (int i = 0; i < numData-1; ++i)
	{
		dClass = (vClass[i+1]+1)/2;
		cost +=-dClass * log(probability(vOpen[i],vClose[1])) - (1 - dClass) *  log(1 - probability(vOpen[i],vClose[i]));
	}
	cost = (double) 1/(numData-1) * cost;
	return cost;
}


void 
LogisticRegression::setEta(double newEta)
{
	eta = newEta;
}
double 
LogisticRegression::probability(double open, double close)
{
	return (1 / (1 + exp((-1) * (vWeights[0] * open) + (vWeights[1] * close))));
}
int 
LogisticRegression::validate(double open, double close)
{
	std::cout << "Probabilidad Regresion Logistica: ";
	std::cout << probability(open,close) <<'\t';
	if(probability(open, close) > 0.5)
		return 1;

	return -1;
}