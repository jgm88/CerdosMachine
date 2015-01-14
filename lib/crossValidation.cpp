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

	// Perceptron perc = Perceptron(2, learningRate);
	// LinearRegression linReg = LinearRegression();
	// LogisticRegression logReg = LogisticRegression(2,learningRate);
	// NeuralNetwork neuNet = NeuralNetwork(learningRate);

	std::string nomAlgo = "";
	float right = 0;
    float error = 0;
	
	float rightTotal = 0;
	float errorTotal = 0;
	
	for (int i = 0; i < k; ++i)
	{
		divide(vClass, vOpen, vClose);
		Perceptron perc = Perceptron(2, learningRate);
		MultiLinearRegression mLinReg = MultiLinearRegression(learningRate);
		LogisticRegression logReg = LogisticRegression(2,learningRate);
		NeuralNetwork neuNet = NeuralNetwork(learningRate);

	    switch(algorithm)
	    {
	    	case 1:	perc.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
	    			nomAlgo = "Perceptron";
	    			if(sDraw.isOn){
	    				drawByFlood(perc);
	    			}	
	    		break;
    		case 2:	mLinReg.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
    				nomAlgo = "Regresion Lineal Multiple";
	    			if(sDraw.isOn){
	    				drawByFlood(mLinReg);
	    			}	
	    		break;
    		case 3:	logReg.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
    				nomAlgo = "Regresion Logistica";
	    			if(sDraw.isOn){
	    				drawByFlood(logReg);
	    			}	
	    		break;
	    	case 4:	neuNet.train(numIterations, numDataTrain, trainClass, trainOpen, trainClose);
	    			nomAlgo = "Red Neuronal";
	    			if(sDraw.isOn){
	    				drawByFlood(neuNet);
	    			}	
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
				case 2: check = mLinReg.validate(testOpen[i], testClose[i]);
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

	float averangeRight = rightTotal / k;
	float averageError = errorTotal / k;

	float percentageRight = percentage(averangeRight);
	float percentajeError = percentage(averageError);
	
		std::cout << "--------------------------------------------------------------------------\n"
			<< "- Media aciertos totales: " << averangeRight << " Media errores totales: " << averageError <<'\n'
			<< "- Porcentaje aciertos:    " << percentageRight << "%"<<"   Porcentaje errores: " << percentajeError <<"%" <<'\n'
			<< "--------------------------------------------------------------------------\n";
}

float CrossValidation::percentage(float right)
{
	return ((right * 100) /numDataTest);	
}
void CrossValidation::drawByFlood(Perceptron p){
    ofstream file;
    string sFile;

	stringstream ssFile;
	ssFile << "plot/pFlood" << index << ".data";

    file.open(ssFile.str());

    for (double i = sDraw.minOpen ; i < sDraw.maxOpen; i+=0.5)
    {
		for (double j = sDraw.minClose ; j < sDraw.maxClose; j+=0.01)
    	{
    		file << p.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
    	}    	
    }

    file.close();
}
void CrossValidation::drawByFlood(LinearRegression linR){
    ofstream file;
    string sFile;

	stringstream ssFile;
	ssFile << "plot/linrFlood" << index << ".data";

    file.open(ssFile.str());

    for (double i = sDraw.minOpen ; i < sDraw.maxOpen; i+=0.5)
    {
		for (double j = sDraw.minClose ; j < sDraw.maxClose; j+=0.01)
    	{
    		file << linR.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
    	}    	
    }

    file.close();

}
void CrossValidation::drawByFlood(MultiLinearRegression mLinR){
    ofstream file;
    string sFile;

	stringstream ssFile;
	ssFile << "plot/mlinrFlood" << index << ".data";

    file.open(ssFile.str());

    // cout << "minOpen " << sDraw.minOpen 	<< endl;
    // cout << "maxOpen " << sDraw.maxOpen 	<< endl;
    // cout << "minClose " << sDraw.minClose 	<< endl;
    // cout << "maxClose " << sDraw.maxClose 	<< endl;

    for (double i = sDraw.minOpen ; i < sDraw.maxOpen; i+=0.5)
    {
		for (double j = sDraw.minClose ; j < sDraw.maxClose; j+=0.01)
    	{
    		file << mLinR.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
    	}    	
    }

    file.close();

}
void CrossValidation::drawByFlood(LogisticRegression logR){
    ofstream file;
    string sFile;

	stringstream ssFile;
	ssFile << "plot/logrFlood" << index << ".data";

    file.open(ssFile.str());

    for (double i = sDraw.minOpen ; i < sDraw.maxOpen; i+=0.5)
    {
		for (double j = sDraw.minClose ; j < sDraw.maxClose; j+=0.01)
    	{
    		file << logR.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
    	}    	
    }

    file.close();

}
void CrossValidation::drawByFlood(NeuralNetwork nn){
    ofstream file;
    string sFile;

	stringstream ssFile;
	ssFile << "plot/nnFlood" << index << ".data";

    file.open(ssFile.str());

    for (double i = sDraw.minOpen ; i < sDraw.maxOpen; i+=0.5)
    {
		for (double j = sDraw.minClose ; j < sDraw.maxClose; j+=0.01)
    	{
    		file << nn.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
    	}    	
    }

    file.close();

}