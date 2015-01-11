#include "machineLearning.h" // colocar las librerias aki
#include <iostream>
#include <fstream>
#include <string.h>
#include <list>

using namespace std;

const char delimiter = ',';
std::vector<int> vClass;
std::vector<double> vOpen;
std::vector<double> vClose;
int numTest=229;
int numTrain=230; 

bool procesarLinea(string linea, int numMuestra)
{
	std::string::size_type sz;
    string aux = "";
    int pos = 0;
    bool isValida= false;
    for (unsigned int i = 0; i < linea.size(); ++ i)
    {
        if(linea[i] != delimiter)
        {
            aux += linea[i];
        }
        else
        {
            switch(pos)
            {
                case 0: //vClass[numMuestra] = stoi(aux, &sz);
                	vClass.push_back(stoi(aux, &sz));
                    break;
                case 1: //vOpen[numMuestra] = stod(aux, &sz);
                	
                	vOpen.push_back(stod(aux, &sz));
                    break;
                case 2: //vClose[numMuestra] = stod(aux, &sz); 
                	
                	vClose.push_back(stod(aux, &sz));
                    break;
                default: cout << "Demasiados argumentos en el documento" << endl;
                    break;
            }

            aux = "";
            pos ++;
        }
    }
    if(pos==3)
    	isValida=true;

    return isValida;
}

// void perceptron(int numIterations, int numSamples, double alpha)
// {
//     int acierto = 0;
//     int error = 0;
// 	Perceptron perc = Perceptron(2, alpha);
//     perc.trainPerceptron(numIterations, numSamples, vClass, vOpen, vClose);

//     // if(perc.validate(open[180],close[180])== vClass[181])
//     // 	cout << "predice!"<< endl;
//     cout << endl << "PRUEBAS PERCEPTRON: " <<endl;
//     acierto= 0;
//     error=0;
//     for (int i = numTest; i < numDatos-1; ++i)
//     {
//     	int comprobar = perc.validate(vOpen[i], vClose[i]);
//     	if (vClass[i+1] == comprobar)
//     	{
//     		acierto++; 
//     	}
//     	else
//     	{
//     		error++;
//     	}
//     }
//     cout << "Aciertos: " << acierto << " Errores: " << error <<endl;

//   //   ofstream ficheroDatos;
//   //   ficheroDatos.open("fulldatos.dat");

//   //   for (float i = 26.5 ; i < 39.5; i+=0.01)
//   //   {
// 		// for (float j = 26.5 ; j < 39.5; j+=0.01)
//   //   	{
//   //   		ficheroDatos << perc.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
//   //   	}    	
//   //   }

//   //   ficheroDatos.close();

// }
// void logisticRegression(int numIterations, int numSamples, double eta)
// {
// 	int acierto;
// 	int error;
// 	LogisticRegression lr = LogisticRegression(eta, 2);
// 	lr.train(numIterations, numSamples, vClass, vOpen, vClose);

// 	cout << endl << "PRUEBAS REGRESION LOGISTICA: " <<endl;
//     acierto= 0;
//     error=0;
//     for (int i = numTest; i < numDatos-1; ++i)
//     {
//     	int comprobar = lr.validate(vOpen[i], vClose[i]);
//     	// cout << "Clase :"<< vClass[i+1]<< endl;
//     	if (vClass[i+1] == comprobar)
//     	{
//     		acierto++; 
//     	}
//     	else
//     	{
//     		error++;
//     	}
//     }
//     cout << "Aciertos: " << acierto << " Errores: " << error <<endl;
// }
// void linearRegression(int numIterations, int numSamples, double eta)
// {
//     int acierto;
//     int error;
//     LinearRegression lr = LinearRegression();

//     lr.train(numIterations, numSamples, vOpen, vClose);

//     cout << endl << "PRUEBAS REGRESION LINEAL: " <<endl;
//     acierto= 0;
//     error=0;
//     for (int i = numTest; i < numDatos-1; ++i)
//     {
//         int comprobar = lr.validate(vOpen[i], vClose[i]);
//         if (vClass[i+1] == comprobar)
//         {
//             acierto++; 
//         }
//         else
//         {
//             error++;
//         }
//     }
//     cout << "Aciertos: " << acierto << " Errores: " << error <<endl;
// }
// Recive el puntero del fichero de entrada
void lecturaFichero(ifstream* ficheroEntrada)
{
	string cadena="";
	int numMuestra=0;
	while(!ficheroEntrada->eof())
	{
	    getline((*ficheroEntrada), cadena);
	    if(procesarLinea(cadena, numMuestra))
	    	numMuestra ++;	
	    
	} 
	for (int i = 0; i < vClass.size(); ++i)
    {
    	cout<< "Clase "<< vClass[i]<< ":::"<< "Open "<<vOpen[i]<< ":::"<< "Close "<<vClose[i]<<endl;
    }
}
void init(int tipoModelo, char useCV, int numIterations, double learningRate )
{
	// CrossValidation cv(5,vClass.size(),learningRate,numIterations);
	if(useCV=='s')
	{
		// cv.average(vClass,vOpen,vClose,tipoModelo);	
	}
	switch(tipoModelo)
    {
    	case 1:
    		
    	case 2:
    	case 3:
    	case 4:
    	default:
    		cout << "ERROR: Tipo de modelo incorrecto"<< endl;
    }
}

void menu()
{
	char tipoModelo ,useCV;
	int numIterations=0,learningRate=0, modelo=0;
	bool fail= false;
	string nombreFicheroEntrada="";
	ifstream ficheroEntrada;

	cout << "*******MACHINE LEARNING*******"<< endl;
	cout << "*******    by CPCr2    *******"<< endl;
	do{
		cout << "******************************"<< endl;
		cout << "**Introduce ruta del fichero**"<< endl;
		cin >> nombreFicheroEntrada ;
		ficheroEntrada.open(nombreFicheroEntrada.c_str());
		if(!ficheroEntrada.is_open())
			fail= true;
		else
			lecturaFichero(&ficheroEntrada);
	}while(fail);

	do{
		cout << "*************************************"<< endl;
		cout << "**Introduce Modelo de entrenamiento**"<< endl;
		cout << "[1] - Perceptron"<< endl;
		cout << "[2] - Regresion Logistica"<< endl;
		cout << "[3] - Regresion Lineal"<< endl;
		cout << "[4] - Red Neuronal"<< endl;//??
		cin >> tipoModelo;	
		
	}while(tipoModelo!='1' && tipoModelo!='2' && tipoModelo!='3' && tipoModelo!='4');
	modelo= tipoModelo - '0';
	cout << "*************************************"<< endl;
	cout << "**Usar Cross-Validation[s/n]**"<< endl;
	cin >> useCV;
	if(useCV!='s' && useCV!='n') useCV='s';

	cout << "**************************************"<< endl;
	cout << "**Iteraciones para ajustar el modelo**"<< endl;
	cout << "**Iteraciones Minimas: 100"<< endl;
	cin >> numIterations;
	if(numIterations<100) numIterations = 1000;

	cout << "**************************************"<< endl;
	cout << "**         Learning rate  **"<< endl;

	cin>> learningRate;
	if(learningRate > 5) learningRate= 0.5;

}


void initWithArgs(int argc, char* argv[])
{
	string nombreFicheroEntrada =argv[1];// ;
	// int tipoModelo=stoi(argv[2]);
	// string useCV= argv[3];
	// int numIterations= stoi(argv[4]);
	// double learningRate=stod(argv[5]) ;

    ifstream ficheroEntrada;
    ficheroEntrada.open(nombreFicheroEntrada.c_str());

    if(ficheroEntrada.is_open())
    {
      lecturaFichero(&ficheroEntrada);
    }
    else
    {
        cout << "ERROR: " << nombreFicheroEntrada << " no encontrado" << endl;
    }
}



int main(int argc, char* argv[]) // numero cachos, algoritmo a usar, num iteraciones
{ 
    if(argc >1)
    {
        initWithArgs(argc,argv);
        /* * * * * * * * * * * * * * * *
		 * ALGORITOMOS DE APRENDIZAJE  *
         * * * * * * * * * * * * * * * */
         //CrossValidation(numAlgoritm);
     //    perceptron(500,220, 0.2);
    	// logisticRegression(500, 220, 0.5);
     //    linearRegression(500, 220, -1);

        // CrossValidation cv = CrossValidation(5, 250);
        // cv.average(vClass, open, close, 1);    
    }
    else
    {
    	menu();
        // cout << "ERROR: Número de parámetros incorrecto." << endl;
        // cout << "Ejemplo de uso:" << endl;
        // cout << "./perceptron datos.cvs" << endl;
    }   
    return 0;
}