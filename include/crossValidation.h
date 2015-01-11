#ifndef CROSSVALIDATION_H
#define CROSSVALIDATION_H

#include "perceptron.h"

class CrossValidation
 {
 public:
 	CrossValidation();
 	CrossValidation(int newK, int newNumData);
 	~CrossValidation();

 	void divide(int vClass[], double vOpen[], double vClose[]);
 	void average(int vClass[], double vOpen[], double vClose[]);
 private:
 	int k;
 	int numData;
 	int numDataTest;
 	int numDataTrain;
 	int index;

	std::vector<int> testClass;
	std::vector<double> testOpen;
	std::vector<double> testClose;

	std::vector<int> trainClass;
	std::vector<double> trainOpen;
	std::vector<double> trainClose;
 }; 
#endif