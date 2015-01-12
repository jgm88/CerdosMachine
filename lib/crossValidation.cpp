#include "crossValidation.h"

CrossValidation::CrossValidation(){}
CrossValidation::CrossValidation(int newK, int newNumData, double newLearningRate, int newNumIterations)
{
	k = newK;
	numData = newNumData;
	learningRate = newLearningRate;
	numIterations = newNumIterations;

 	numDataTest = numData / k;
 	numDataTrain = numData - numDataTest;
 	index = 1;
}
CrossValidation::~CrossValidation(){}

void 
CrossValidation::divide(std::vector<int> vClass, std::vector<double> vOpen, std::vector<double> vClose)
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
CrossValidation::average(std::vector<int> vClass, std::vector<double> vOpen, std::vector<double> vClose, int algorithm)
{
	/*	
		algorithm:
		1 == Perceptron
		2 == Regresion Lineal
		3 == Regresion Logistica
		4 == Red Neuronal
	*/

	Perceptron perc = Perceptron(2, learningRate);
	LinearRegression linReg = LinearRegression();
	LogisticRegression logReg = LogisticRegression(learningRate,2);
	NeuralNetwork neuNet = NeuralNetwork(learningRate);

	std::string nomAlgo = "";
	int right = 0;
    int error = 0;
	
	int rightTotal = 0;
	int errorTotal = 0;
	
	for (int i = 0; i < k; ++i)
	{
		divide(vClass, vOpen, vClose);

	    switch(algorithm)
	    {
	    	case 1:	perc.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
	    			nomAlgo = "Perceptron";
	    		break;
    		case 2: linReg.train(numIterations, numDataTrain, trainOpen, trainClose);
    				nomAlgo = "Regresion Lineal";
	    		break;
    		case 3:	logReg.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
    				nomAlgo = "Regresion Logistica";
	    		break;
	    	case 4:	neuNet.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
	    			nomAlgo = "Red Neuronal";
	    		break;
	    }
		

		right = 0;
		error = 0;

		for (int i = 0; i <=numDataTest; ++i)
		{
			int check;
			switch(algorithm)
			{
				case 1: check = perc.validate(testOpen[i], testClose[i]);
					break;
				case 2: check = linReg.validate(testOpen[i], testClose[i]);
	    			break;
    			case 3:	check = logReg.validate(testOpen[i], testClose[i]);
	    			break;
	    		case 4:	check = neuNet.validate(testOpen[i], testClose[i]);
	    			break;
				default: check = 0;
			}

			if (testClass[i+1] == check)
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

		std::cout << "--> Cross Validation con "<< nomAlgo<<", pasada " << i+1 << " de " << k << '\n' 
				<< "--> Aciertos: " << right << " Errores: " << error <<'\n'
				<< '\n';
	}

	int averangeRight = rightTotal / k;
	int averageError = errorTotal / k;

	int percentageRight = percentage(averangeRight);
	int percentajeError = percentage(averageError);
	
		std::cout << "--------------------------------------------------------------------------\n"
			<< "- Media aciertos totales: " << averangeRight << " Media errores totales: " << averageError <<'\n'
			<< "- Porcentaje aciertos:    " << percentageRight << "%"<<"   Porcentaje errores: " << percentajeError <<"%" <<'\n'
			<< "--------------------------------------------------------------------------\n";
}

int CrossValidation::percentage(int right)
{
	return ((right * 100) /numDataTest);	
}