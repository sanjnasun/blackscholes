#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "options.h"

// ----------------------------------------------------------------------------------------
//                        "User Input" Class Declarations - requires options
// ----------------------------------------------------------------------------------------

class input {
public:
    void inputReader(Options* op); //reads in inputs via prompts
    input(); //default constructor
    bool isValidOptionType(const std::string& type); //validates options and allows procession
    bool isValidDouble(double value); //valid double input
    double readDoubleInput(const std::string& prompt); //reading in double values for T
    std::string readStringInput(const std::string& prompt); //reading string value for T



private:
    template<typename T>
    T getInput(const std::string& prompt); //receiving input with prompt with Template usage

    std::vector<double> values; // Vector to hold option values
    
    //Set index for the vector 
    static const int OPTION_TYPE_INDEX = 0;
    static const int PRICE_INDEX = 1;
    static const int STRIKE_PRICE_INDEX = 2;
    static const int EXPIRATION_DATE_INDEX = 3;
    static const int RISK_RATE_INDEX = 4;
    static const int VOLATILITY_INDEX = 5;
};
