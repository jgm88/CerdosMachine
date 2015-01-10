#include "machineLearning.h" // colocar las librerias aki
#include <iostream>
#include <fstream>
#include <string.h>
#include <list>

using namespace std;

list<string> lineasProcesadas;
const char delimiter = '\t';
std::string::size_type sz;		// alias of size_t
const int numDatos = 100;		//CAMBIAR EL VALOR LECTURA A VOLUNTAD
int vClass[numDatos];
double open[numDatos];
double close[numDatos];
double pesos[3] = {0.33, 0.33, 0.33};
double umbral = 0.5;
double coeficiente = 0.01;
int numTest= 89;
int numTrain= 90;
std::vector< std::vector<double> > dataSet;
void procesarLinea(string linea, int numMuestra)
{
    string aux = "";
    int pos = 0;

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
                case 0: vClass[numMuestra] = stoi(aux, &sz);
                    break;
                case 1: open[numMuestra] = stod(aux, &sz);
                    break;
                case 2: close[numMuestra] = stod(aux, &sz); 
                    break;
                default: cout << "Demasiados argumentos en el documento" << endl;
                    break;
            }

            aux = "";
            pos ++;
        }
    }
}

void perceptron(int numIterations, int numSamples, double alpha)
{
    int acierto = 0;
    int error = 0;
	Perceptron perc = Perceptron(2, alpha);
    perc.trainPerceptron(numIterations, numSamples, vClass, open, close);

    // if(perc.validate(open[180],close[180])== vClass[181])
    // 	cout << "predice!"<< endl;
    cout << endl << "PRUEBAS PERCEPTRON: " <<endl;
    acierto= 0;
    error=0;
    for (int i = numTest; i < numDatos-1; ++i)
    {
    	int comprobar = perc.validate(open[i], close[i]);
    	if (vClass[i+1] == comprobar)
    	{
    		acierto++; 
    	}
    	else
    	{
    		error++;
    	}
    }
    cout << "Aciertos: " << acierto << " Errores: " << error <<endl;

  //   ofstream ficheroDatos;
  //   ficheroDatos.open("fulldatos.dat");

  //   for (float i = 26.5 ; i < 39.5; i+=0.01)
  //   {
		// for (float j = 26.5 ; j < 39.5; j+=0.01)
  //   	{
  //   		ficheroDatos << perc.validate(i,j) << '\t'<< i << '\t'<< j<< std::endl;
  //   	}    	
  //   }

  //   ficheroDatos.close();

}
void logisticRegression(int numIterations, int numSamples, double eta)
{
	int acierto;
	int error;
	LogisticRegression lr = LogisticRegression(eta, 2);
	lr.train(numIterations, numSamples, vClass, open, close);

	cout << endl << "PRUEBAS REGRESION LOGISTICA: " <<endl;
    acierto= 0;
    error=0;
    for (int i = numTest; i < numDatos-1; ++i)
    {
    	int comprobar = lr.validate(open[i], close[i]);
    	cout << "Clase :"<< vClass[i+1]<< endl;
    	if (vClass[i+1] == comprobar)
    	{
    		acierto++; 
    	}
    	else
    	{
    		error++;
    	}
    }
    cout << "Aciertos: " << acierto << " Errores: " << error <<endl;
}
int main(int argc, char* argv[]) 
{ 
    string nombreFicheroEntrada = argv[1];
    ifstream ficheroEntrada;
    string cadena;
    int subConjunto= numDatos/5;
    int numMuestra = 0;
    dataSet = std::vector< std::vector<double> > (5,std::vector<double>(subConjunto));
    if(argc == 2)
    {
        ficheroEntrada.open(nombreFicheroEntrada.c_str());

        if(ficheroEntrada.is_open())
        {
            while(!ficheroEntrada.eof() && numMuestra < numDatos)
            {
                getline(ficheroEntrada, cadena);
                procesarLinea(cadena, numMuestra);
                
                numMuestra ++;
            } 
        }
        else
        {
            cout << "ERROR: " << nombreFicheroEntrada << " no encontrado" << endl;
        }

        ficheroEntrada.close();

        /* * * * * * * * * * * * * * * *
		 * ALGORITOMOS DE APRENDIZAJE  *
         * * * * * * * * * * * * * * * */
        perceptron(500,numTrain, 0.02);
    	logisticRegression(500, numTrain, 0.0005);
    }
    else
    {
        cout << "ERROR: Número de parámetros incorrecto." << endl;
        cout << "Ejemplo de uso:" << endl;
        cout << "./perceptron datos.cvs" << endl;
    }   
}