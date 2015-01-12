#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

std::vector<string> lineasProcesadas;
const char delimiter = ',';
std::string::size_type sz;     // alias of size_t

void procesarLinea(string linea)
{
    string aux = "";
    string auxLinea = "";
    double open, high, low, close, volume = 0, maxSubMin;
    int pos = 0;

    for (int i = 0; i < linea.size(); ++i)
    {
        if(linea[i] != delimiter)
        {
            aux += linea[i];
        }
        else
        {
            switch(pos)
            {
                case 0: aux = "";
                    break;
                case 1: open = stod(aux, &sz);                    
                    break;
                case 2: high = stod(aux, &sz);
                    break;
                case 3: low = stod(aux, &sz);
                    break;
                case 4: close = stod(aux, &sz);                    
                    break;
                case 5: volume = stod(aux, &sz); //cout << "volume" << volume << endl;
                    break;
                default: cout << "Demasiados argumentos en el documento" << endl;
                    break;
            }

            aux = "";
            pos ++;
        }
    }

    // cout << "LINEA: " << open << ", " << high << ", " << low << ", " << close << ", " << volume << ", " << endl;
    // cout << volume << endl;

    maxSubMin = high - low;
    float openSubClose = open - close;

    int sube = -1;

    if(openSubClose >= 0)
    {
        sube = 1;
    }

    auxLinea += to_string(sube);
    auxLinea += "\t";
    auxLinea += to_string(open);
    auxLinea += "\t";
    auxLinea += to_string(close);
    auxLinea += "\t";
    // auxLinea += ",";

    lineasProcesadas.push_back(auxLinea);
}

int main(int argc, char* argv[]) 
{ 
        
    ifstream ficheroDatos;
    ofstream ficheroProcesado;
    string cadena;
    
    if(argc == 3)
    {
        string nombreFicheroEntrada = argv[1];
        string nombreFicheroSalida = argv[2];

        ficheroDatos.open(nombreFicheroEntrada.c_str());

        if(ficheroDatos.is_open())
        {

            while(!ficheroDatos.eof())
            {
                getline(ficheroDatos, cadena);

                procesarLinea(cadena);
            } 
        }
        else
        {
            cout << "ERROR: " << nombreFicheroEntrada << " no encontrado" << endl;
        }

        ficheroDatos.close();

        ficheroProcesado.open(nombreFicheroSalida.c_str());

        if(ficheroProcesado.is_open())
        {

            for (std::vector<string>::iterator i = lineasProcesadas.begin(); i != lineasProcesadas.end(); ++i)
            {
                ficheroProcesado << *i << endl;
            }
        }
        else
        {
            cout << "ERROR: No se ha podido crear el fichero de salida" << endl;
        }
    }
        else
    {
        cout << "ERROR: Número de parámetros incorrecto." << endl;
        cout << "Ejemplo de uso:" << endl;
        cout << "./preprocesador data/entrada.csv data/salida.data" << endl;
    }
}