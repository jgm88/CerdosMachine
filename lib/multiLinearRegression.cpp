#include "multiLinearRegression.h"

using namespace arma;


void train(int iterations, int numData, std::vector<int> vClass, std::vector<double> vOpen,std::vector<double> vClose){
	
	mat X = randu<mat>(3, 2);

	//Bias requiere anyadir una columna 1.0

	mat Y = eye<mat>(3, 1);

	//Obtenemos la traspuesta
	mat Xt = X.t();

	// //traspuesta por original
	mat XtX = Xt * X;

	// //Calculamos la inversa de X*Xt
	// mat invXtX = XtX.i(); 

	// // Multiplicamos Xt * Y
	// mat XtY = Xt * Y;

	// //Aplicamos la formula final ((Xt * X)^-1) * Xt*Y
	// mat betaMatrix = invXtX * XtY;

}