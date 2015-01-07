#include <iostream>
#include <fstream>
#include <string.h>
#include <list>

using namespace std;

list<string> lineasProcesadas;
const char delimiter = ',';
std::string::size_type sz;     // alias of size_t
int sube[5];
float open[5];
float close[5];
float pesos[3] = {0.33, 0.33, 0.33};
float umbral = 0.5;
float coeficiente = 0.01;

void procesarLinea(string linea, int numMuestra)
{
    string aux = "";
    int pos = 0;

    for (int i = 0; i < linea.size(); ++ i)
    {
        if(linea[i] != delimiter)
        {
            aux += linea[i];
        }else
        {
            switch(pos)
            {
                case 0: sube[numMuestra] = stoi(aux, &sz);
                break;
                case 1: open[numMuestra] = stof(aux, &sz);
                break;
                case 2: close[numMuestra] = stof(aux, &sz); 
                break;
                default: cout << "Demasiados argumentos en el documento" << endl;
                break;
            }

            aux = "";
            pos ++;
        }
    }
}

int main(int argc, char* argv[]) 
{ 
    string nombreFicheroEntrada = argv[1];
    ifstream ficheroEntrada;
    string cadena;

    int numMuestra = 0;

    if(argc == 2)
    {
        ficheroEntrada.open(nombreFicheroEntrada.c_str());

        if(ficheroEntrada.is_open())
        {
            while(!ficheroEntrada.eof() && numMuestra < 5)
            {
                getline(ficheroEntrada, cadena);

                procesarLinea(cadena, numMuestra);

                numMuestra ++;
            } 
        }else
        {
            cout << "ERROR: " << nombreFicheroEntrada << " no encontrado" << endl;
        }

        ficheroEntrada.close();

        // Hacer cosas con los datos
        for(int i = 0; i < 5; i ++)
        {
            cout << sube[i] << "," << open[i] << "," << close[i] << endl;
        }

    }else
    {
        cout << "ERROR: Número de parámetros incorrecto." << endl;
        cout << "Ejemplo de uso:" << endl;
        cout << "./perceptron datos.cvs" << endl;
    }   
}