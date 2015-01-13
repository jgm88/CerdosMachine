#include "logisticRegression.h"

LogisticRegression::LogisticRegression(){}
LogisticRegression::~LogisticRegression(){}
LogisticRegression::LogisticRegression(int inputs,double newEta)
{
	vWeights = std::vector<double> (inputs, 0);
	eta = newEta;
	w0=-1;
}

void 
LogisticRegression::train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen, std::vector<double> vClose)
{
	int sClass;
	double oldEta=eta;
	// double gradient;
	double J,oldJ=0;
	double peso0=0,peso1=0;
	vWeights[0]=0,vWeights[1]=0;
	while(iterations > 0)//0 && !isMinErr )
	{
		J= calculateCost(numData,vClass,vOpen,vClose);
		// std::cout << "Coste de iteracion "<< iterations<< ": "<< J <<std::endl;
		if(oldJ<J)
			eta/=100;
			// std::cout << "iterations "<< iterations << " Soy mayor"<< std::endl;

		peso0=peso1=0;
		// gradient=0;
		for (int i = 0; i < numData-1; ++i)
		{
			// la clase que entre esta definida con -1 y 1
			// hacemos la siguiente operaciones para definirla entre 0 y 1
			sClass = (vClass[i+1]+1)/2; 

			peso0+= (sigmoid(vOpen[i],vClose[i])-sClass)*vOpen[i];
			peso1+= (sigmoid(vOpen[i],vClose[i])-sClass)*vClose[i];

			// Formula de Yaser para minimizar el Error
			// gradient += (double)(sClass * vOpen[i]) / (1 + exp(sClass * vWeights[0] * vOpen[i]));
			// gradient += (double)(sClass * vClose[i]) / (1 + exp(sClass * vWeights[1] * vClose[i]));
		}
		// gradient *= (double)-1/ (numData-1);
		vWeights[0] -= eta*(peso0/double(numData-1));
		vWeights[1] -= eta*(peso1/double(numData-1));

		// vWeights[0] -= eta*(gradient/double(numData-1));
		// vWeights[1] -= eta*(gradient/double(numData-1));

		oldJ=J;
		--iterations;
	}
	eta= oldEta;
	// std::cout << "Peso0 " << vWeights[0] << std::endl;
	// std::cout << "Peso1 "<< vWeights[1] << std::endl; 
}
void 
LogisticRegression::setEta(double newEta)
{
	eta = newEta;
}
double 
LogisticRegression::sigmoid(double open, double close)
{
	return (double) (1.0 / (1.0 + exp((-1.0) * (w0+ (vWeights[0] * open) + (vWeights[1] * close)))));
}
int 
LogisticRegression::validate(double open, double close)
{
	// std::cout << "Probabilidad Regresion Logistica: ";
	// std::cout << sigmoid(open,close) <<'\t';
	if(sigmoid(open, close) > 0.5)
		return 1;

	return -1;
}
// Funcion que calcula el coste del error en la iteraciones i del bucle de entrenamiento
// Cada vez que recalculamos los pesos debemos recalcular el coste
double
LogisticRegression::calculateCost(int numData,std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose)
{
	double cost = 0, dClass;
	for (int i = 0; i < numData-1; ++i)
	{
		dClass = (vClass[i+1]+1)/2;
		cost +=dClass * log(sigmoid(vOpen[i],vClose[i])) + (1 - dClass) *  log(1 - sigmoid(vOpen[i],vClose[i]));
	}
	cost *= (-1/ double (numData-1));
	return cost;
}