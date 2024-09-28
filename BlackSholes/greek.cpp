#include "greek.h"
#include <iostream>
#include <math.h>
#include <cmath>


//returning the gamma value, edge cases for valid inputs have already been taken to account to within the black scholes
//O(n) runtime
double Greeks::calculateGamma(Options* op, BlackSholes* bl)
{
    double gam = bl->cdf(bl->d1Value_) / op->price_ / op->volatility_ / std::sqrt(op->expiration_);
    setGamma(gam);
    return gam;
}

//returning a double value of vega, not dependnent on call or put option. O(n) runtime
double Greeks::calculateVega(Options* op, BlackSholes* bl)
{
    double vega = op->price_ + bl->cdf(bl->d1Value_) * std::sqrt(op->expiration_);
    setGamma(vega);
    return vega;
}


//-------------differences in call and puts----------------------//


double Greeks::calculateDelta(Options* op, BlackSholes* bl) //retursn a dobule delta value, focus on volaility
{
    if (this->findType(op)) //call option return 
    {
        double delt = this->cdf(bl->d1Value_);
        setDelta(delt);
        return delt;
    }
    else {
        double delt = (this->cdf(bl->d1Value_) - 1); //for the put option
        setDelta(delt);
        return delt;
    }
}


//uses all values from options to determine the theta value, dependnet of call and put 
double Greeks::calulateTheta(Options* op, BlackSholes* bl)
{
    double d = (std::log(op->price_ / op->strikePrice_) + op->expiration_ * (op->riskRate_ + 0.5 * op->volatility_ * op->volatility_))
        / (op->volatility_ * std::sqrt(op->expiration_));
   
    if (this->findType(op))
    {
        double theta = -op->price_ * this->cdf(bl->d1Value_) * op->volatility_ / 2 /
            std::sqrt(op->expiration_) - op->riskRate_ * op->strikePrice_ * 
            std::exp(-op->riskRate_ * op->expiration_) * this->cdf(bl->d1Value_ - op->volatility_ * std::sqrt(op->expiration_));
        setDelta(theta);
        return theta;
    }
    else {
        double theta = -op->price_ * this->cdf(bl->d1Value_) * op->volatility_ / 2 /
            std::sqrt(op->expiration_) - op->riskRate_ * op->strikePrice_ *
            std::exp(-op->riskRate_ * op->expiration_) * 
            this->cdf( op->volatility_ * std::sqrt(op->expiration_) - bl->d1Value_);
        setDelta(theta);
        return theta;
    }
}

//calculates the rho values, uses all op otion values and d1 and d2
double Greeks::calculateRho(Options* op, BlackSholes* bl)
{
    if (this->findType(op))
    {
        double rho = op->expiration_ * op->strikePrice_ * std::exp(-op->riskRate_ * op->expiration_) * this->cdf(bl->d1Value_ - op->volatility_ * std::sqrt(op->expiration_));
        setDelta(rho);
        return rho;
    }
    else {
        double rho = -op->expiration_ * op->strikePrice_ * std::exp(-op->riskRate_ * op->expiration_) * 
            this->cdf(op->volatility_ * 
                std::sqrt(op->expiration_)* bl->d1Value_ - 1);
        setDelta(rho);
        return rho;
    }
}



//--------------------------getter + setter----------------------------------//

void Greeks::setDelta(double delt)
{
    delta_ = delt;
}

void Greeks::setGamma(double gam)
{
    gamma_ = gam;
}

void Greeks::setVega(double vega)
{
    vega_ = vega;
}

void Greeks::setTheta(double theta)
{
    theta_ = theta;
}

void Greeks::setRho(double rho)
{
    rho_ = rho;
}

double Greeks::getDelta()
{
    return delta_;
}

double Greeks::getGamma()
{
    return gamma_;
}

double Greeks::getVega()
{
    return vega_;
}

double Greeks::getTheta()
{
    return theta_;
}

double Greeks::getRho()
{
    return rho_;
}


