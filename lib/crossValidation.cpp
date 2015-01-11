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
		
		// Debug
		// if(i == numData-1)
		// 	std::cout << "|--> de " << initTest << " a " << endTest <<'\n';
	}

	if(index < k)
	{
		++index;
	}
	else
	{
		index = 1;
	}
}
void 
CrossValidation::average(int vClass[], double vOpen[], double vClose[], int algorithm)
{
	// algorithm:
	// 1 == Perceptron
	// 2 == Regresion Lineal
	// 3 == Regresion Logistica
	// ...
	Perceptron perc = Perceptron(2, 0.02);
	LinearRegression linReg = LinearRegression();
	// LogicalRegresion logReg = LogicalRegresion();

    int cTrainClass[numDataTrain];
    double cTrainOpen[numDataTrain];
    double cTrainClose[numDataTrain];

    int cTestClass[numDataTest];
    double cTestOpen[numDataTest];
    double cTestClose[numDataTest];

	int right = 0;
    int error = 0;
	
	int rightTotal = 0;
	int errorTotal = 0;
	
	for (int i = 0; i < k; ++i)
	{
		divide(vClass, vOpen, vClose);

		std::copy(trainClass.begin(), trainClass.end(), cTrainClass);
	    std::copy(trainOpen.begin(), trainOpen.end(), cTrainOpen);
	    std::copy(trainClose.begin(), trainClose.end(), cTrainClose);

	    std::copy(testClass.begin(), testClass.end(), cTestClass);
	    std::copy(testOpen.begin(), testOpen.end(), cTestOpen);
	    std::copy(testClose.begin(), testClose.end(), cTestClose);

	    switch(algorithm)
	    {
	    	case 1:	perc.trainPerceptron(500, numDataTrain, cTrainClass, cTrainOpen, cTrainClose);
	    		break;
    		case 2: linReg.train(500, numDataTrain, cTrainOpen, cTrainClose);
	    		break;
    		case 3://logReg.train(500, numDataTrain, cTrainClass, cTrainOpen, cTrainClose);
	    		break;
	    }
		

		right = 0;
		error = 0;

		for (int i = 0; i < numDataTest; ++i)
		{
			int check;
			switch(algorithm)
			{
				case 1: check = perc.validate(cTestOpen[i], cTestClose[i]);
					break;
				case 2: check = linReg.validate(cTestOpen[i], cTestClose[i]);
	    			break;
    			case 3:	//check = logReg.validate(cTestOpen[i], cTestClose[i]);
	    			break;
				default: check = 0;
			}

			if (cTestClass[i+1] == check)
			{
				++right;
				++rightTotal; 
			}
			else
			{
				++error;
				++errorTotal;
			}
		}
		std::cout << "--> Cross Validation con Perceptron, pasada " << i+1 << " de " << k << '\n' ;
		std::cout << "--> Aciertos: " << right << " Errores: " << error <<'\n';
		std::cout << '\n';
	}
	int averangeRight = rightTotal / k;
	int averageError = errorTotal / k;
	std::cout << "--------------------------------------------------------------------------\n";
	std::cout << "- Media aciertos totales: " << averangeRight << " Media errores totales: " << averageError <<'\n';
	std::cout << "--------------------------------------------------------------------------\n";
}