#pragma once
#ifndef MONTE_CARLO
#define MONTE_CARLO

#include "options.h"
#include "vector"
#include <mutex>

#include <boost/random/mersenne_twister.hpp> 
#include <boost/random/normal_distribution.hpp> 
#include <boost/random/variate_generator.hpp> 


// ----------------------------------------------------------------------------------------
//                        "Monte Carlo" Class Declarations - requires options
// ----------------------------------------------------------------------------------------


class monteCarlo : public Options {

public:
	double brownonian_motion; //publci data members
	double monte_carlo_val;


	double valGenerator(boost::variate_generator<boost::mt19937, boost::normal_distribution<> >& generator); //uses boost library generators , genreates random value 
	//double BrownonianModel(Options* op, double random);
	double MonteCarloSimulator(Options* op); //uses generator, and cholesky to determine paths + increments to dtermeine value
	std::vector<std::vector<double>> Cholesky_Decomposition(const std::vector<std::vector<double>>& matrix); //cholesky decomposiiton of a matrix



	//-------------getter and setters-------------//

	// Time complexity: O(1) - gets the gbm type value  
	// Space complexity: O(1)
	double getGBM(); 

	// Time complexity: O(1) - gets the monte carlo type value  
	// Space complexity: O(1)
	double getMonteCarlo();


	// Time complexity: O(1) - sets the gbm type value  
	// Space complexity: O(1)
	void setGBM(double val);

	// Time complexity: O(1) - sets the mote carlo type value  
	// Space complexity: O(1)
	void setMonteCarlo(double val);
	
	//std::mutex mtx;



};










#endif // MONTE_CARLO
