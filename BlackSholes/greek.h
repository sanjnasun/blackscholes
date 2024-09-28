#pragma
#ifndef GREEKS
#define GREEKS


#include "blacksholes.h"


// ----------------------------------------------------------------------------------------
//                        "Greeks" Class Declarations - requires BlackScholes
// ----------------------------------------------------------------------------------------

class Greeks: public BlackSholes {

public:
	double delta_;
	double gamma_;
	double vega_;
	double theta_;
	double rho_;

	Greeks() //CONSTRUCTOR
		: delta_(0.0), gamma_(0.0), vega_(0.0), theta_(0.0), rho_(0.0) {}

	// Parameterized Constructor
	Greeks(double delta, double gamma, double vega, double theta, double rho,
		double dist, double d1, double d2, double callValue, double putValue)
		:  delta_(delta), gamma_(gamma), vega_(vega), theta_(theta), rho_(rho) {}
		 
	
	//Greeks values can only be configured after the black scholes object/value has been determiend, these provide additional input with them
	double calculateDelta(Options* op, BlackSholes* bl); //calculates teh delta value as a change of the option and bl object
	double calculateGamma(Options* op, BlackSholes* bl); //calcualtes the gamma value
	double calculateVega(Options* op, BlackSholes* bl); //calcualtes vega, with both op, and bl
	double calulateTheta(Options* op, BlackSholes* bl); //calcualtes theta
	double calculateRho(Options* op, BlackSholes* bl); //calculates rho



	//---------Getter and setters--------------//
	void setDelta(double delt);
	void setGamma(double gam);
	void setVega(double vega);
	void setTheta(double theta);
	void setRho(double rho);

	double getDelta();
	double getGamma();
	double getVega();
	double getTheta();
	double getRho();


 };





#endif





