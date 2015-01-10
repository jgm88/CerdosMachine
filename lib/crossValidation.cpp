#include "crossValidation.h"

CrossValidation::CrossValidation(){}
CrossValidation::CrossValidation(int newK, int newNumData)
{
	k = newK;
	numData = newNumData;

 	numDataTest = numData / k;
 	numDataTrain = numData - numDataTest;
 	index = 1;
}
CrossValidation::~CrossValidation(){}

void 
CrossValidation::divide(int vClass[], double vOpen[], double vClose[])
{
	testClass.clear();
	testOpen.clear();
	testClose.clear();
	trainClass.clear();
	trainOpen.clear();
	trainClose.clear();

	int initTest = numDataTest * (index - 1);
	int endTest = numDataTest * index;

	for (int i = 0; i < numData; ++i)
	{
		if(initTest <= i && i <= endTest)
		{
			testClass.push_back(vClass[i]);
			testOpen.push_back(vOpen[i]);
			testClose.push_back(vClose[i]);
		}
		else
		{
			trainClass.push_back(vClass[i]);
			trainOpen.push_back(vOpen[i]);
			trainClose.push_back(vClose[i]);
		}
	}

	if(index < k)
		++index;
	else
		index = 1;
}
void 
CrossValidation::average(int vClass[], double vOpen[], double vClose[])
{
	int acierto = 0;
    int error = 0;

    int cTrainClass[numDataTrain];
    double cTrainOpen[numDataTrain];
    double cTrainClose[numDataTrain];

    int cTestClass[numDataTest];
    double cTestOpen[numDataTest];
    double cTestClose[numDataTest];

    std::copy(trainClass.begin(), trainClass.end(), cTrainClass);
    std::copy(trainOpen.begin(), trainOpen.end(), cTrainOpen);
    std::copy(trainClose.begin(), trainClose.end(), cTrainClose);

    std::copy(testClass.begin(), testClass.end(), cTestClass);
    std::copy(testOpen.begin(), testOpen.end(), cTestOpen);
    std::copy(testClose.begin(), testClose.end(), cTestClose);

	Perceptron perc = Perceptron(2, 0.02);

	for (int i = 0; i < k; ++i)
	{
		divide(vClass, vOpen, vClose);
		perc.trainPerceptron(500, numDataTrain, cTrainClass, cTrainOpen, cTrainClose);
	
		acierto = 0;
		error = 0;
		for (int i = numData; i < numData-1; ++i)
		{
			int comprobar = perc.validate(cTestOpen[i], cTestClose[i]);
			if (cTestClass[i+1] == comprobar)
			{
				acierto++; 
			}
			else
			{
				error++;
			}
		}
		std::cout << "Cross Validation con Perceptron" << i << "de " << k << '\n' ;
		std::cout << "Aciertos: " << acierto << " Errores: " << error <<'\n';
	}
}