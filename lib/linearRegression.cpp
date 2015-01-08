#include "linearRegression.h"

LinearRegression::LinearRegression(){}
LinearRegression::~LinearRegression(){}

LinearRegression::LinearRegression(int countX, float betaZero);
{
	srand(time(0));
	this->betaZero = betaZero;
	
	//TODO CAMBIAR A VECTOR

	beta1 = (double)(rand()) / (double)RAND_MAX; 
	beta2 = (double)(rand()) / (double)RAND_MAX;
    
}