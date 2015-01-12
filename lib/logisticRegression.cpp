#include "logisticRegression.h"

LogisticRegression::LogisticRegression(){}
LogisticRegression::~LogisticRegression(){}
LogisticRegression::LogisticRegression(double newEta, int inputs)
{
	vWeights = std::vector<double> (inputs, 0);
	eta = newEta;
}

void 
LogisticRegression::train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen, std::vector<double> vClose)
{
	int sClass;
	double gradient;
	while(iterations > 0)//0 && !isMinErr )
	{
		for (int i = 0; i < numData-1; ++i)
		{
			// la clase que entre esta definida con -1 y 1
			// hacemos la siguiente operaciones para definirla entre 0 y 1
			sClass = (vClass[i+1]+1)/2; 

			// Formula de Yaser para minimizar el Error
			gradient += (double)(sClass * vOpen[i]) / (1 + exp(sClass * vWeights[0] * vOpen[i]));
			gradient += (double)(sClass * vClose[i]) / (1 + exp(sClass * vWeights[1] * vClose[i]));
		}
		gradient *= (double)-1/ (numData-1);
		vWeights[0] -= eta*gradient;
		vWeights[1] -= eta*gradient;

		--iterations;
	}
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
	// std::cout << "Probabilidad Regresion Logistica: ";
	// std::cout << probability(open,close) <<'\t';
	if(probability(open, close) > 0.5)
		return 1;

	return -1;
}
// Funcion que calcula el coste del error en la iteraciones i del bucle de entrenamiento
// Cada vez que recalculamos los pesos debemos recalcular el coste
// double
// LogisticRegression::calculateCost(int numData, int vClass[], double vOpen[], double vClose[])
// {
// 	double cost = 0, dClass;
// 	for (int i = 0; i < numData-1; ++i)
// 	{
// 		dClass = (vClass[i+1]+1)/2;
// 		cost +=-dClass * log(probability(vOpen[i],vClose[1])) - (1 - dClass) *  log(1 - probability(vOpen[i],vClose[i]));
// 	}
// 	cost = (double) 1/(numData-1) * cost;
// 	return cost;
// }