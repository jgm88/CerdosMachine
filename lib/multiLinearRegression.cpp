#include "multiLinearRegression.h"

using namespace arma;

MultiLinearRegression::MultiLinearRegression(){
	this->eta = 0.00003; 
	threshold = 0.0001;
	beta0 = 0;
	beta1 = 0;
	beta2 = 0;
}
MultiLinearRegression::MultiLinearRegression(double eta){
	this->eta = eta;
	threshold = 0.0001;
	beta0 = 0;
	beta1 = 0;
	beta2 = 0;
}
MultiLinearRegression::MultiLinearRegression(double b0, double b1, double b2){
	this->eta = 0.00003; 
	threshold = 0.0001;
	beta0 = b0;
	beta1 = b1;
	beta2 = b2;
}
MultiLinearRegression::~MultiLinearRegression(){}


void MultiLinearRegression::printWeight(){
	
	cout << "Beta0 : "<< beta0 << endl;
	cout << "Beta1 : "<< beta1 << endl;
	cout << "Beta2 : "<< beta2 << endl;
}


int MultiLinearRegression::validate(double open, double close){

	// cout << calculate(open, close) << endl;

	if(calculate(open,close)>0) 
		return 1;
	return -1;
}

double MultiLinearRegression::calculate(double x1, double x2){
	// cout << " SALIDA : " << beta0 + beta1*x1 + beta2*x2 <<endl;
	return (beta0 + beta1*x1 + beta2*x2);
}

double MultiLinearRegression::cost(int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose){

	double cost = 0;
	double costAux = 0;
	for (int i = 0; i < numData-1; ++i)
	{
		costAux = calculate(vOpen[i],vClose[i]) - vClass[i+1];
		cost += costAux * costAux;
	}
	return cost/((double)(numData-1)*2);
}

void MultiLinearRegression::train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose){
	


	//Bias requiere anyadir una columna 1.0

	mat X(numData-1, 3);

	for(int i = 0; i < numData-1; ++i){
		X(i,0) = 1;
		X(i,1) = vOpen[i];
		X(i,2) = vClose[i];
	}

	 // X.print("X : ");

	mat Y(numData-1, 1);

	for(int i = 0; i < numData-1; ++i)
		Y(i) = vClass[i+1];

	 // Y.print("Y : ");

	//Obtenemos la traspuesta
	mat Xt = X.t();

	// // //traspuesta beta0 + beta1*x1 + beta2*x2por original
	mat XtX = Xt * X;

	// //Calculamos la inversa de X*Xt
	mat invXtX = XtX.i(); 

	// // Multiplicamos Xt * Y
	mat XtY = Xt * Y;

	// //Aplicamos la formula final ((Xt * X)^-1) * Xt*Y
	mat mBeta = invXtX * XtY;

	// mBeta.print("BETA : ");

	// mBeta.print("BETA : ");

	beta0 = mBeta(0,0);
	beta1 = mBeta(1,0);
	beta2 = mBeta(2,0);

	//REAJUSTAMOS 
	// Funcion coste J y variables auxiliares
	
	double J, oldJ = std::numeric_limits<double>::max();
	double fixingBeta0, fixingBeta1, fixingBeta2;
	double costAux;
	int i;

	for (int iters = 0; iters < iterations; ++iters){

		J = cost(numData, vClass, vOpen, vClose);

		if((abs(abs(oldJ) - abs(J))) < threshold){ 
			break;
		}

		fixingBeta0 = 0;
		fixingBeta1 = 0;
		fixingBeta2 = 0;
		costAux = 0;

		for(i = 0; i < numData-1; ++i){

			//h de theta
			costAux = calculate(vOpen[i],vClose[i]) - vClass[i+1];

			fixingBeta0 += costAux;
			fixingBeta1 += costAux * vOpen[i];
			fixingBeta2 += costAux * vClose[i];
		}

		fixingBeta0 -= (fixingBeta0/((double)(numData-1)))*eta;
		fixingBeta1 -= (fixingBeta1/((double)(numData-1)))*eta;
		fixingBeta2 -= (fixingBeta2/((double)(numData-1)))*eta;

		beta0 = fixingBeta0;
		beta1 = fixingBeta1;
		beta2 = fixingBeta2;

		oldJ = J;
	}
}