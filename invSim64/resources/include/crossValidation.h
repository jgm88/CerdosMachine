#ifndef CROSSVALIDATION_H
#define CROSSVALIDATION_H

#include "machineLearning.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

typedef struct 
{
	bool isOn = false;
	double maxOpen = 0;
	double minOpen = 0;
	double maxClose = 0;
	double minClose = 0;
	
}DrawingStruct;

class CrossValidation
 {
 public:
 	CrossValidation();
 	CrossValidation(int newK, int newNumData, double newLearningRate, int newNumIterations);
 	~CrossValidation();

 	void divide(std::vector<int> vClass, std::vector<double> vOpen, std::vector<double> vClose);
 	void average(std::vector<int> vClass, std::vector<double> vOpen, std::vector<double> vClose, int algorithm);
 	float percentage(float right);

	DrawingStruct sDraw;

 private:
 	double learningRate;
 	int numIterations;

 	//Iteraciones
 	int k;
 	int numData;
 	int numDataTest;
 	int numDataTrain;
 	//Numero de iteracion del cross
 	int index;

	std::vector<int> testClass;
	std::vector<double> testOpen;
	std::vector<double> testClose;

	std::vector<int> trainClass;
	std::vector<double> trainOpen;
	std::vector<double> trainClose;

	void drawByFlood(Perceptron p);
	void drawByFlood(LinearRegression linR);
	void drawByFlood(LogisticRegression logR);
	void drawByFlood(NeuralNetwork nn);
 }; 
#endif