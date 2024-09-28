#include "montecarlosim.h"
#include <math.h>
#include <cmath>
#include <iostream>


//GLOBAL INLINE VALUES - rho, pahts, and incrmentes. will always remain consant
inline const double rho = -0.5; 
inline const int path = 10000;
inline const int increments = 1000;


//functiont to use boost vairante generator + normal distrubtion to return a genrator function, using psuedo ranodm 
double monteCarlo::valGenerator(boost::variate_generator<boost::mt19937, boost::normal_distribution<>>& generator)
{
    return generator();
}

//returns a decomposed vector with cholesky matrix algorithm, decomposes for monte carlo of randomized values
std::vector<std::vector<double>> monteCarlo::Cholesky_Decomposition(const std::vector<std::vector<double>>& matrix)
{
    size_t n = matrix.size();
    std::vector<std::vector<double>> lower(n, std::vector<double>(n, 0.0));

    for (size_t i = 0; i < n; i++) { //reviewing both top and bottom values, then taking in teh lwoer matrix sums
        for (size_t j = 0; j <= i; j++) {
            double sum = 0.0;
            if (j == i) {
                for (size_t k = 0; k < j; k++) {
                    sum += lower[j][k] * lower[j][k];
                }
                lower[j][j] = sqrt(matrix[j][j] - sum);
            }
            else { //decomposing of lower values 
                for (size_t k = 0; k < j; k++) {
                    sum += lower[i][k] * lower[j][k];
                }
                lower[i][j] = (matrix[i][j] - sum) / lower[j][j];
            }
        }
    }

    return lower;
}


double monteCarlo::MonteCarloSimulator(Options* op)
{
    // Define the correlation matrix (for single asset, this is more of a learning exercise)
    std::vector<std::vector<double>> correlationMatrix(2, std::vector<double>(2));
    correlationMatrix[0][0] = 1.0; // Variance of the first factor (price)
    correlationMatrix[0][1] = rho; // Correlation between price and volatility
    correlationMatrix[1][0] = rho; 
    correlationMatrix[1][1] = 1.0; 

    // cholesky decomposition
    std::vector<std::vector<double>> choleskyMatrix = Cholesky_Decomposition(correlationMatrix);

    // random number generator
    boost::mt19937 rng(time(0));
    boost::normal_distribution<> dist(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > generator(rng, dist);

    // variables for simulation
    std::vector<double> pricePath(increments, op->price_);
    double totalPayoff = 0.0;

    // Simulate paths
    for (int i = 0; i < path; ++i) {
        // Generate correlated random variables
        std::vector<double> normalRandom(increments);
        std::vector<double> correlatedRandom(increments);

        for (size_t j = 0; j < increments; ++j) {
            normalRandom[j] = generator();
            correlatedRandom[j] = normalRandom[j] * choleskyMatrix[0][0] + generator() * choleskyMatrix[1][0];
        }

        // Simulate the asset price path
        for (size_t j = 1; j < increments; ++j) {
            double dt = op->expiration_ / increments;
            double drift = (op->riskRate_ - 0.5 * pow(op->volatility_, 2)) * dt;
            double diffusion = op->volatility_ * sqrt(dt) * correlatedRandom[j];

            pricePath[j] = pricePath[j - 1] * exp(drift + diffusion);
        }

        // Calculate the payoff for the final price
        double finalPrice = pricePath[increments - 1];
        double payoff = 0.0;
        if (op->optionType_ == "call") {
            payoff = std::max(finalPrice - op->strikePrice_, 0.0);
        }
        else if (op->optionType_ == "put") {
            payoff = std::max(op->strikePrice_ - finalPrice, 0.0);
        }

        totalPayoff += payoff;
    }

    // Return the discounted average payoff
    return (totalPayoff / path) * exp(-op->riskRate_ * op->expiration_);
}









//-------------------------------Getters and Setters-----------------------------------//
double monteCarlo::getGBM()
{
    return this->brownonian_motion;
}

double monteCarlo::getMonteCarlo()
{
    return this->monte_carlo_val;
}

void monteCarlo::setGBM(double val)
{
    brownonian_motion = val;
}

void monteCarlo::setMonteCarlo(double val)
{
    monte_carlo_val = val;
}



