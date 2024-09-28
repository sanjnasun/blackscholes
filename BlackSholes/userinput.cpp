#include "userinput.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "options.h"
#include <algorithm>



inline std::string optionType; //global variable used by all functions


bool input::isValidOptionType(const std::string& type) { //checks for valid input of option type
    //std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    return type == "call" || type == "put" || type == "Call " || type == "Put";
}

// validate if input double is greater than or equal to 0
bool input::isValidDouble(double value) {
    return value >= 0.0;
}

// read a double from input with validation
double input::readDoubleInput(const std::string& prompt) {
    double value;
    std::string line;
    int count = 0;
    while (true && count < 2) { //only allows two attemps, or else project is terminated
        std::cout << prompt;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        if (iss >> value && iss.eof() && isValidDouble(value)) {
            return value;
        }
        std::cerr << "Invalid input. Please enter a positive number.\n";
        count++;
    }
}

// read string from input with validation
std::string input::readStringInput(const std::string& prompt) {
    std::string value;
    int count = 0;
    while (true && count < 2) {
        std::cout << prompt;
        std::getline(std::cin, value);
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        if (isValidOptionType(value)) {
            return value;
        }
        std::cerr << "Invalid input. Please enter 'call' or 'put'.\n";
        count++;
    }
}

template<typename T> //function to receive input with prompt, uses above function helpers
T input::getInput(const std::string& prompt) {
    if constexpr (std::is_same<T, std::string>::value) {
        return readStringInput(prompt);
    }
    else if constexpr (std::is_same<T, double>::value) {
        return readDoubleInput(prompt);
    }
    else {
        throw std::runtime_error("Unsupported type");
    }
}


void input::inputReader(Options* op) { //Function to actually read via manual input. 
    std::cout << "You have chosen to enter manual information.\nThis simulation will return a Black Scholes and Monte Carlo simulation estimates, and Greek values." << std::endl;
    std::cout << "Begin entering the values for the options: strike price, initial price, volatility, time to expiration (days), and option type" << std::endl;

    values.resize(6); //using a set vector to hold values

    optionType = getInput<std::string>("Enter Option Type (call or put): ");
    std::transform(optionType.begin(), optionType.end(), optionType.begin(), ::tolower);

    if (optionType == "call") { //setting double value in vector based on call/put for easier use
        values[OPTION_TYPE_INDEX] = 1.0; 
    }
    else if (optionType == "put") {
        values[OPTION_TYPE_INDEX] = 0.0; 
    }
    else {
        std::cerr << "Invalid option type entered. Exiting program. " << std::endl;
        values[OPTION_TYPE_INDEX] = 0.0; // Default to 0.0 if invalid input
        std::exit(EXIT_FAILURE);
    }

    values[PRICE_INDEX] = getInput<double>("Enter the Price of the option (euros): ");
    values[STRIKE_PRICE_INDEX] = getInput<double>("Enter the Strike Price (euros): ");
    values[EXPIRATION_DATE_INDEX] = getInput<double>("Enter the Expiration Date (days): ");
    values[RISK_RATE_INDEX] = getInput<double>("Enter Risk Rate Interest (percent): ");
    values[VOLATILITY_INDEX] = getInput<double>("Enter Volatility (percent): ");

    //printing vlaues for verifiction
   /* std::cout << "\n\nEntered values:" << std::endl;
    std::cout << "Option Type: " << (values[OPTION_TYPE_INDEX] == 1.0 ? "call" : "put") << std::endl;
    std::cout << "Price: " << values[PRICE_INDEX] << std::endl; 
    std::cout << "Strike Price: " << values[STRIKE_PRICE_INDEX] << std::endl;
    std::cout << "Expiration Date: " << values[EXPIRATION_DATE_INDEX] << std::endl;
    std::cout << "Risk Rate Interest: " << values[RISK_RATE_INDEX] << std::endl;
    std::cout << "Volatility: " << values[VOLATILITY_INDEX] << std::endl;*/

    //std::cout << "HOLA \n";


    //setting values of options
    op->setPrice(values[PRICE_INDEX]);
    op->setStrikePrice(values[STRIKE_PRICE_INDEX]);
    op->setRiskRate(values[RISK_RATE_INDEX]);
    op->setExpirationDate(values[EXPIRATION_DATE_INDEX]/365.0);
    op->setVoltaility(values[VOLATILITY_INDEX]);
    op->setOptionType(optionType);
}


input::input() //DEFAULT CONSTRUCTOR
{}


