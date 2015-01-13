#include "machineLearning.h" // colocar las librerias aki
#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <limits>

using namespace std;

const char delimiter = '\t';
std::vector<int> vClass;
std::vector<double> vOpen;
std::vector<double> vClose;
int numTest=0;
int numTrain=0; 

//Variables que delimitan el rango del floodDrawing
double maxOpen = 0;
double minOpen = std::numeric_limits<double>::max();
double maxClose = 0;
double minClose = std::numeric_limits<double>::max();

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
                    if(stod(aux, &sz) > maxOpen) maxOpen = stod(aux, &sz);
                    if(stod(aux, &sz) < minOpen) minOpen = stod(aux, &sz);                   
                    break;
                case 2: //vClose[numMuestra] = stod(aux, &sz); 
                	
                	vClose.push_back(stod(aux, &sz));      
                    if(stod(aux, &sz) > maxClose) maxClose = stod(aux, &sz);
                    if(stod(aux, &sz) < minClose) minClose = stod(aux, &sz);               
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

void perceptron(int numIterations, double alpha)
{
    int acierto = 0;
    int error = 0;
	Perceptron perc = Perceptron(2, alpha);
    perc.train(numIterations, numTrain, vClass, vOpen, vClose);

    cout << endl << "PRUEBAS PERCEPTRON: " <<endl;
    for (unsigned int i = numTest; i < vClass.size()-1; ++i)
    {
    	int comprobar = perc.validate(vOpen[i], vClose[i]);
    	if (vClass[i+1] == comprobar)
    		acierto++; 
    	else
    		error++;
    }
    cout << "Aciertos: " << acierto << " Errores: " << error <<endl;
}
void logisticRegression(int numIterations, double eta)
{
	int acierto=0;
	int error=0;
	LogisticRegression lr = LogisticRegression(2,eta);
	lr.train(numIterations, numTrain, vClass, vOpen, vClose);

	cout << endl << "PRUEBAS REGRESION LOGISTICA: " <<endl;
    for (unsigned int i = numTest; i < vClose.size()-1; ++i)
    {
    	int comprobar = lr.validate(vOpen[i], vClose[i]);
    	if (vClass[i+1] == comprobar)
    		acierto++; 
    	else
    		error++;
    }
    cout << "Aciertos: " << acierto << " Errores: " << error <<endl;
}
void linearRegression(int numIterations, double eta)
{
    int acierto=0;
    int error=0;
    LinearRegression lr = LinearRegression();

    lr.train(numIterations, numTrain, vOpen, vClose);

    cout << endl << "PRUEBAS REGRESION LINEAL: " <<endl;
    for (unsigned int i = numTest; i < vClose.size()-1; ++i)
    {
        int comprobar = lr.validate(vOpen[i], vClose[i]);
        if (vClass[i+1] == comprobar)
            acierto++; 
        else
            error++;
    }
    cout << "Aciertos: " << acierto << " Errores: " << error <<endl;
}
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

	numTrain= vClass.size()-30;
	numTest= vClass.size()-31;
	// for (int i = 0; i < vClass.size(); ++i)
	// {
	// 	cout<< "Clase "<< vClass[i]<< ":::"<< "Open "<<vOpen[i]<< ":::"<< "Close "<<vClose[i]<<endl;
	// }
}
void init(int tipoModelo, char drawFlood, int numIterations, double learningRate)
{
	CrossValidation cv(5,vClass.size(),learningRate,numIterations);

    if(drawFlood == 's')
        cv.sDraw.isOn = true;
    cv.sDraw.maxOpen = maxOpen;
    cv.sDraw.minOpen = minOpen;
    cv.sDraw.maxClose = maxClose;
    cv.sDraw.minClose = minClose;

	cv.average(vClass,vOpen,vClose,tipoModelo);	
}

void menu()
{
	char tipoModelo ,drawFlood;
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
		cout << "[2] - Regresion Lineal"<< endl;
        cout << "[3] - Regresion Logistica"<< endl;
		cout << "[4] - Red Neuronal"<< endl;//??
		cin >> tipoModelo;	
		
	}while(tipoModelo!='1' && tipoModelo!='2' && tipoModelo!='3' && tipoModelo!='4');
	modelo= tipoModelo - '0';
	cout << "*************************************"<< endl;
	cout << "**Generar fichero para FloodDrawing [s/n]**"<< endl;
	cin >> drawFlood;
	if(drawFlood!='s' && drawFlood!='n') drawFlood='s';

	cout << "**************************************"<< endl;
	cout << "**Iteraciones para ajustar el modelo**"<< endl;
	cout << "**Iteraciones Minimas: 100"<< endl;
	cin >> numIterations;
	if(numIterations<100) numIterations = 1000;

	cout << "**************************************"<< endl;
	cout << "**         Learning rate            **"<< endl;

	cin>> learningRate;
	if(learningRate > 5) learningRate= 0.5;

	init(modelo,drawFlood, numIterations, learningRate );
}

void initWithArgs(int argc, char* argv[])
{
	string nombreFicheroEntrada =argv[1];// ;
	int tipoModelo=stoi(argv[2]);
	string drawFlood= argv[3];
	int numIterations= stoi(argv[4]);
	double learningRate=stod(argv[5]) ;

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
    init(tipoModelo,drawFlood[0],numIterations,learningRate);
}

int main(int argc, char* argv[]) // numero cachos, algoritmo a usar, num iteraciones
{ 
	if(argc == 6)
    {
        initWithArgs(argc,argv);   
    }
    else
    {
    	menu();
    }   
    return 0;
}
