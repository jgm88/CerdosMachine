#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <limits>

class LogisticRegression
{
public:
	LogisticRegression();
	~LogisticRegression();
	LogisticRegression(int inputs,double newEta);
	LogisticRegression(double w0, double vWeight1, double vWeight2);
	void printWeight();
	double calculateCost(int numData,std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
	void train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
	double sigmoid(double open, double close);
	int validate(double open, double close);
	void setEta(double newEta);
private:
	void init();
	std::vector<double> vWeights;
	double eta;
	double w0;
	double oldEta;
	double threshold;
	double minValue;
};
#endif