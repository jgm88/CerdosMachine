#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <iostream>
#include <vector>
#include <stdlib.h>

class LinearRegression
{
public:
    LinearRegression();
    LinearRegression(float betaZero);
    ~LinearRegression();

//TODO CAMBIAR ENTRADAS A VECTOR

	//con las Y y los regresores ajustaremos las betas
    void train(int iterations, int numData, double vX[], double vY[]);
    void setBetaZero(double newBetaZero);
    float validate(double x, double y);

private:

	//Constante BethaZero (desplazamiendo respecto al origen 0 < B < 1)
    float betaZero;

//TODO CAMBIAR PESOS A VECTOR
    
	//Influencia de las variables de entrada
    double beta1;

    //Y = BjXj + B0 + Error
    float error;
};


#endif