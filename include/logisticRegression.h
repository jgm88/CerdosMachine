#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

class LogisticRegression
{
public:
	LogisticRegression();
	~LogisticRegression();
	LogisticRegression(double newEta, int inputs);

	// double calculateCost(int numData, int vClass[], double vOpen[], double vClose[]);
	void train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose);
	double probability(double open, double close);
	int validate(double open, double close);
	void setEta(double newEta);
private:
	std::vector<double> vWeights;
	double eta;

};
#endif