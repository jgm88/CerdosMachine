#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <iostream>
#include <vector>
#include <stdlib.h>

#include <armadillo>

class MultiLinearRegression
{
public:

	MultiLinearRegression();
	~MultiLinearRegression();
	void train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
	int validate(double open, double close);

private:
	
	double beta0;
	double beta1;
	double beta2;
};


#endif