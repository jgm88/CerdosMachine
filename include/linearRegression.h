#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

class LinearRegression
{
public:
    LinearRegression();
    LinearRegression(int countX, float betaZero);
    ~LinearRegression();

	//con las Y y los regresores ajustaremos las betas
    void calculate(int iterations, int numData, float vY[], double vX1[], double vX2[]);
    void setBetaZero(double newBetaZero);
    float getY(double x1, double x2);

private:

	//Constante BethaZero (desplazamiendo respecto al origen 0 < B < 1)
    float betaZero;

    //Influencia de las variables de entrada
    double beta1;
    double beta2;

    //Y = BjXj + B0 + Error
    float error;
};


#endif