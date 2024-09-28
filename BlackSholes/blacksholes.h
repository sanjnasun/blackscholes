#pragma once
#ifndef BLACKSHOLES_P
#define BLACKSHOLES_P

#include "options.h"


// ----------------------------------------------------------------------------------------
//                        "User Input" Class Declarations - requires options
// ----------------------------------------------------------------------------------------


class BlackSholes : public Options{

public:
	double distribution_;
	double d1Value_;
	double d2Value_;
	double callVal_;
	double putVal_;

	BlackSholes()
		: distribution_(0.0), d1Value_(0.0), d2Value_(0.0), callVal_(0.0), putVal_(0.0) {}

	// Parameterized Constructor
	BlackSholes(double dist, double d1, double d2, double callValue, double putValue)
		: distribution_(dist), d1Value_(d1), d2Value_(d2), callVal_(callValue), putVal_(putValue) {}

	//Parameterized Constructor that initializes from Options
	BlackSholes(double dist, double d1, double d2, double callValue, double putValue,
		const Options& options)
		: distribution_(dist), d1Value_(d1), d2Value_(d2), callVal_(callValue), putVal_(putValue) {}

	void d1(Options* op); //calculates the d1 determeinate value

	void d2(Options* op); //calculates the d2 determinte value
	
	double erf(double x); //distribution method using a d1 val
	double cdf(double x); //cumulative distrubtion method
	double pdf(double x); //probability density fucntion 
	 

	double Boole(double start, double end, int x); //integration using boole methology
	 
	double calculateCallOptionPrice(Options* op); //calculates teh call option

	double calculatePutOptionPrice(Options* op); //calculates the put option


	//------Getter and Setters------------//
	
	// Time complexity: O(1) - sets the D1 value  
	// Space complexity: O(1)
	void setD1(double d1); 
	
	// Time complexity: O(1) - sets the D2 value  
	// Space complexity: O(1)
	void setD2(double d2);

	// Time complexity: O(1) - sets the call value value  
	// Space complexity: O(1)
	void setCallVal(double call);

	// Time complexity: O(1) - sets the put option value  
	// Space complexity: O(1)
	void setPutVal(double put);

	// Time complexity: O(1) - gets the D1 value  
	// Space complexity: O(1)
	double getD1();

	// Time complexity: O(1) - gets the D2 value  
	// Space complexity: O(1)
	double getD2();

	// Time complexity: O(1) - sets the call value  
	// Space complexity: O(1)
	double getCall();
	
	// Time complexity: O(1) - gets the put option value  
	// Space complexity: O(1)
	double getPut();

	// Time complexity: O(1) - dtereines if option is call or put, retursn t or f  
	// Space complexity: O(1)
	bool findType(Options* op);

	~BlackSholes(); //destructor 

	
};



#endif




