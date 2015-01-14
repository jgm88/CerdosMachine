#ifndef MULTILINEARREGRESSION_H
#define MULTILINEARREGRESSION_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <math.h>

#include <armadillo>

class MultiLinearRegression
{
public:

	MultiLinearRegression();
	MultiLinearRegression(double eta);
	MultiLinearRegression(double b0, double b1, double b2);
	~MultiLinearRegression();
	void train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
	
	int validate(double open, double close);
	double calculate(double x1, double x2);
	double cost(int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
	void printWeight();

private:
	
	double threshold;

	double eta;

	double beta0;
	double beta1;
	double beta2;
};


#endif