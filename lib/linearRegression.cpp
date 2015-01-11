#include "linearRegression.h"

LinearRegression::LinearRegression(){
	betaZero = beta1 = error = 0;
}
LinearRegression::~LinearRegression(){}

LinearRegression::LinearRegression(float betaZero)
{
	this->betaZero = betaZero;
	
	beta1 = 0; 
    
}
void LinearRegression::setBetaZero(double newBetaZero){
	
	this->betaZero = newBetaZero;
}

float LinearRegression::validate(double x, double y){

	double yInLine = x * beta1 + betaZero;
	if(y - yInLine > 0)
		return 1;

	return -1;

}


void LinearRegression::train(int iterations, int numData, double vX[], double vY[]){

	double ySum = 0;
	double xSum = 0;
	double xySum =0;
	double xSumSqr = 0;


		
	for (int i = 0; i < numData-1; ++i)
	{
		ySum += vY[i];
		xSum += vX[i];
		xySum += vX[i] * vY[i];
		xSumSqr += vX[i] * vX[i];
	}

	this->betaZero = ((ySum * xSumSqr) - (xSum * xySum)) / ((numData * xSumSqr) - (xSum * xSum));
	this->beta1 = ((numData * xySum) - (xSum * ySum)) / ((numData * xSumSqr) - (xSum * xSum));

	//for (i = 0; i < numData-1; ++i)
	//recalcular para cada punto la desviacion de Y evaluando cada punto
	// y ajustar la betaZero

		std::cout << '\n' << "Recta Regresion";
		std::cout << "beta1 = " << this->beta1 << '\n';
		std::cout << "BetaZero = " << this->betaZero << '\n';
		std::cout << std::endl;	

}