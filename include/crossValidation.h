#ifndef CROSSVALIDATION_H
#define CROSSVALIDATION_H

#include "machineLearning.h"

class CrossValidation
 {
 public:
 	CrossValidation();
 	CrossValidation(int newK, int newNumData, double newLearningRate, int newNumIterations);
 	~CrossValidation();

 	void divide(int vClass[], double vOpen[], double vClose[]);
 	void average(int vClass[], double vOpen[], double vClose[], int algorithm);
 private:
 	double learningRate;
 	int numIterations;

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