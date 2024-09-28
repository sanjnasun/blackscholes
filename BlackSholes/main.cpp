#include <iostream>
#include <string>
#include <algorithm>
#include "userinput.h"
#include "options.h"
#include "montecarlosim.h"
#include "blacksholes.h"
#include "greek.h"



int main() {
    
 
    std::cout << "Welcome to the Black Scholes Model. Please select between manual input (I), file reader (R), or Quit (q): " << std::endl;
    std::string userChoice;
    std::getline(std::cin, userChoice);

    std::transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);

    if (userChoice == "q") {
        std::cout << "Exiting Program" << std::endl;
        return 0;
    }
    else if (userChoice == "i") {
        Options* op = new Options;
       input* in = new input;
        in->inputReader(op);
       
        //std::cout << op->getOptionType() << "\n";
        
        //get d1, get d2, find balck scholes value
        BlackSholes* bl = new BlackSholes;

        
        bl->d1(op);
        bl->d2(op);
        
        if (op->getOptionType() == "call")
        {
            std::cout << "\n-----------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "\n\nThe black scholes for call value is: " << bl->calculateCallOptionPrice(op) << "\n" << std::endl;
        }
        else
        {
            std::cout << "The black scholes for put value is: " << bl->calculatePutOptionPrice(op) << "\n" << std::endl;
        }

        monteCarlo* mo = new monteCarlo;
        std::cout << "The Monte Carlo simulation value is: " << mo->MonteCarloSimulator(op) << "\n" << std::endl;

        Greeks* gr = new Greeks;
        std::cout << "Gamma: " << gr->calculateGamma(op, bl) << std::endl;
        std::cout << "Vega: " << gr->calculateVega(op, bl) << std::endl;
        std::cout << "Delta: " << gr->calculateDelta(op, bl) << std::endl;
        std::cout << "Theta: " << gr->calulateTheta(op, bl) << std::endl;
        std::cout << "Rho: " << gr->calculateRho(op, bl) << std::endl;
        
        
        delete in; 
        delete op;
        delete bl;
        delete gr;
        delete mo;


       
    }
    else if (userChoice == "r") {
        std::cout << "File reader selected" << std::endl;
    }
    else {
        std::cout << "Invalid input. Please select 'I', 'R', or 'Q'." << std::endl;
    }

    return 0;
}
