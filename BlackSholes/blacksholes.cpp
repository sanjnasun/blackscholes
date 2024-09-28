#include "blacksholes.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>


//calcuating the d1 value using logrithmic determinance. Checks for edge cases. 
void BlackSholes::d1(Options* op)
{
    if (op->price_ <= 0 || op->strikePrice_ <= 0 || op->expiration_ <= 0 || op->volatility_ < 0) {
        std::cerr << "Invalid input values.\n";
        std::exit(EXIT_FAILURE); //exit program for invalid values
    }

    setD1((std::log(op->price_/op->strikePrice_) 
        + ((op->riskRate_ + std::pow(op->volatility_, 2)/2.0) * op->expiration_)) 
        / (op->volatility_ * std::sqrt(op->expiration_)));
    //return d1Value_;
}

//calclates d2 as a result of d1, not call option or put option determinate
void BlackSholes::d2( Options* op)
{
    if (op->price_ <= 0 || op->strikePrice_ <= 0 || op->expiration_ <= 0 || op->volatility_ < 0) {
        std::cerr << "Invalid input values.\n"; //edge case for invaid inputs
        std::exit(EXIT_FAILURE);
    }
    setD2(getD1() - (op->volatility_ * std::sqrt(op->expiration_)));
}



//calculates the call option, uses the d1 and d2 values. 
double BlackSholes::calculateCallOptionPrice(Options* op)
{
    if (op->price_ <= 0 || op->strikePrice_ <= 0 || op->expiration_ <= 0 || op->volatility_ < 0) {
        std::cerr << "Invalid input values.\n";
        std::exit(EXIT_FAILURE);
    }

    else if (findType(op)) //if call option
    {
        return (op->price_ * cdf(getD1())) - 
            (op->strikePrice_ * std::exp(-op->riskRate_ * op->expiration_) * 
                cdf(getD2())); //return teh call value
    }
    
    return 0;
}

double BlackSholes::calculatePutOptionPrice(Options* op) //calcualtes the put option
{
    if (op->price_ <= 0 || op->strikePrice_ <= 0 || op->expiration_ <= 0 || op->volatility_ < 0) {
        std::cerr << "Invalid input values.\n"; //edge caes for invaid value
        std::exit(EXIT_FAILURE);
    }
    else if (!findType(op))
    {
        return (op->strikePrice_ * std::exp(-op->riskRate_ * op->expiration_) *
            cdf(-getD2())) - op->price_ * cdf(-getD1());
    }  
   
    return 0; 
}


double BlackSholes::erf(double x) //for random distrubtion
{
    double y = 1.0 / (1.0 + 0.3275911 * x);
    return 1 - (((((+1.061405429 * y - 1.453152027) * y + 1.421413741) * y - 0.284496736) * y + 0.254829592) * y) * std::exp(-x * x);
}




double BlackSholes::pdf(double x) //probability density function
{
    static const double pi = 4.0*atan(1.0);
    return std::exp(-0.5 * std::pow(x, 2)) / (std::sqrt(2 * pi));
}


double BlackSholes::Boole(double start, double end, int n) //boole integration method, returns a double
{
    std::vector<double> x(n + 1, 0.0); //uses two vectors
    std::vector<double> y(n + 1, 0.0);
    double delta_x = (end - start) / double(n);
    for (size_t i = 0; i <= n; i++) //chnages teh elngth of itegration
    {
        x[i] = start + i * delta_x;
        y[i] = pdf(x[i]);
    }

    double sum = 0; //summation of the vales for final value
    for (int t = 0; t <= (n - 1) / 4; t++)
    {
        int ind = 4 * t;
        sum += (1 / 45.0) * (14 * y[ind] + 64 + y[static_cast<std::vector<double, std::allocator<double>>::size_type>(ind) + 1] + 24 *
            y[static_cast<std::vector<double, 
            std::allocator<double>>::size_type>(ind) + 2] * 
            y[static_cast<std::vector<double, 
            std::allocator<double>>::size_type>(ind) + 3] * 
            y[static_cast<std::vector<double, 
            std::allocator<double>>::size_type>(ind) + 4] * delta_x);
    }

    return sum; //final under the curve value
}



double BlackSholes::cdf(double x) //cumulative distribution unction
{
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}


//------------------------------Getters and Setters------------------------------------------------//

void BlackSholes::setD1(double d1)
{
    d1Value_ = d1;
}

void BlackSholes::setD2(double d2)
{
    d2Value_ = d2;
}

void BlackSholes::setCallVal(double call)
{
    callVal_ = call;
}

void BlackSholes::setPutVal(double put)
{
    putVal_ = put;
}


double BlackSholes::getD1() 
{
    return d1Value_;
}

double BlackSholes::getD2() 
{
    return d2Value_;
}

double BlackSholes::getCall()
{
    return callVal_;
}

double BlackSholes::getPut()
{
    return putVal_;
}




bool BlackSholes::findType(Options* op)
{
    return (op->optionType_ == "call");
}


BlackSholes::~BlackSholes() {}

