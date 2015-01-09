#include "linearRegression.h"

LinearRegression::LinearRegression(){}
LinearRegression::~LinearRegression(){}

LinearRegression::LinearRegression(int countX, float betaZero)
{
	srand(time(0));
	this->betaZero = betaZero;
	
	//TODO CAMBIAR A VECTOR

	beta1 = (double)(rand()) / (double)RAND_MAX; 
	beta2 = (double)(rand()) / (double)RAND_MAX;
    
}
void LinearRegression::setBetaZero(double newBetaZero){
	
	this->betaZero = newBetaZero;
}

float LinearRegression::getY(double x1, double x2){

	//TODO return Y
	return (x1*beta1 + x2 * beta2 + betaZero);
}


void LinearRegression::calculate(int iterations, int numData, float vY[], double vX1[], double vX2[]){

	float y;
	double x1;
	double x2;
	float resultPoint;
   	double beta1;
    double beta2;


    while(iterations > 0)
	{		
		for (int i = 0; i < numData-1; ++i)
		{
			y = vY[i+1];
			x1 = vX1[i];
			x2 = vX2[i];
			resultPoint = 0.5;

		}
		--iterations;
	}
	//for (i = 0; i < numData-1; ++i)
	//recalcular para cada punto la desviacion de Y evaluando cada punto
	// y ajustar la betaZero

		std::cout << '\n' << "Recta Regresion";
		std::cout << "beta1 = " << this->beta1 << '\n';
		std::cout << "beta2 = " << this->beta2 << '\n';
		std::cout << "BetaZero = " << this->betaZero << '\n';
		std::cout << std::endl;	

}