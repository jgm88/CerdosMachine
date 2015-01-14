#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <stack>
#include <list>
#include "../include/logisticRegression.h"
#include "../include/perceptron.h"

std::string::size_type sz; 

//
// Non-Blocking GetLine:
//    Gets a line of characters from a stream, until it finds a delimiter or the timeout passes
//
void nb_getline(std::istream& in, std::string& str,
                char delim = '\n', unsigned timeout = 3) {

    std::stringstream ss;
    char c = 0;

    // Timeout needs to be incremented +1, 'cause 0 does not count
    if (timeout + 1 != 0) timeout++;

    // Read characters while we do not found delimiter or we run out of time
    while ( timeout > 0 && c != delim ) {
        // Get next character (instream should be non-blocking!)
        in.clear();
        in.get(c);

        if (!in.eof()) {
            // Next character found, put it in provisional stream
            if (c != delim) ss << c;
        } else if (ss.str().length() > 0) {
            // Found eof, and we are in the middle of the line
            while (in.eof() && ss.str().length() > 0 && timeout > 0) {
                // Sleep 1 millisecond and try again
                usleep(1000);
                in.clear();
                timeout--;
            }

        // Nothing ready to be read, let's exit
        } else break;
    }

    str = ss.str();
}

//
// Send a Random BUY/SELL command, or nothing
//
void sendRandomCommand()
{
    unsigned r = rand() % 1000;
    double c = (double)(rand() % 1000) / 999.0;
    switch(r) {
        case 0: std::cout << "BUY " << c << std::endl; break;
        case 1: std::cout << "SELL " << c << std::endl; break;
        default: break;
    }
}

void readInformation(std::string linea, double &auxOpen, double &auxClose)
{
    const char delimiter = ' ';
    std::string aux = "";
    std::string auxLinea = "";
    // double date, open, high, low, close, volume = 0;
    double open, close;
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
                case 0: //Estoy cogiendo la cadena NextCandle
                    break;
                case 1:// date = std::stod(aux, &sz);           
                    break;
                case 2: //high = std::stod(aux, &sz);
                    break;
                case 3: open = std::stod(aux, &sz);
                    break;
                case 4: close = std::stod(aux, &sz);                    
                    break;
                case 5: //low = std::stod(aux, &sz); 
                    break;
                case 6: //volume = std::stod(aux, &sz);
                    break;
                default: break;
            }

            aux = "";
            pos ++;
        }
    }

    auxClose = close;
    auxOpen = open;

    // std::cerr << "Date: " << date << 
    //                     ", high: " << high << 
    //                     ", open: " << open <<
    //                     ", close: " << close << 
    //                     ", low: " << low << 
    //                     ", volume: " << volume << '\n';

    // cout << "LINEA: " << open << ", " << high << ", " << low << ", " << close << ", " << volume << ", " << endl;
    // cout << volume << endl;

    
}

void sendCommand(std::string &str)
{
    double open, close;

    readInformation(str, open, close);

    // LogisticRegression lr = LogisticRegression(-0.53679, 0.46321, 0.46321);
    Perceptron pr = Perceptron();

    double c = (double)(rand() % 1000) / 999.0;

    int check = pr.validate(open, close);

    switch(check)
    {
        case 1: std::cout << "BUY " << c << std::endl; break;
        case -1: std::cout << "SELL " << c << std::endl; break;
        default: break;
    }

    // std::cerr << "open: " << open << " close: " << close << std::endl;
}

int main(void)
{
    bool reg = false;
    std::string s = "", subs;

    // Wait for INITIALIZE command
    while (s != "INITIALIZE") {
      nb_getline(std::cin, s);
      usleep(200000);      // Sleep for 0.2 seconds (5 times per second)
    }

    // Register into the match
    std::stringstream ss;
    srand(time(NULL));
    ss << "ply" << rand() % 1000;
    std::cout << "REGISTER " << ss.str() << std::endl;

    // Wait for START command
    subs = "";
    do {
      nb_getline(std::cin, s);
      if (s.length() > 5) {
        subs = s.substr(0, 5);
        std::cerr << "SUBSTR: [" << subs << "]\n";
      }
      usleep(200000);      // Sleep for 0.2 seconds (5 times per second)
    } while (subs != "START");

    // Interpret START command
    ss.clear(); ss.str(s);
    unsigned mode, duration, candletime;
    double initfiat;
    ss >> s >> mode >> duration >> candletime >> initfiat;
    std::cerr << "START " << mode << duration << candletime << initfiat;

    // Until the end of the simulation, BUY and SELL
    while (s != "END") {
        nb_getline(std::cin, s);
        if (s != "")
        {
            std::cerr << "Recibido: (" << s << ")" << std::endl;
            sendCommand(s);
        }

        //* Your Code Here */
        // sendRandomCommand();
        // sendCommand(s);


        usleep(50000);      // Sleep for 0.05 seconds (20 times per second)
    }

    return 0;
}
