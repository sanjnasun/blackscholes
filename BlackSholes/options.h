#pragma once
#ifndef OPTIONS
#define OPTIONS

#include <string>

// ----------------------------------------------------------------------------------------
//                        "Options" Class Declarations - used for inheritance
// ----------------------------------------------------------------------------------------


class Options {

private: double PrivateVariable=0.0;

public: 
	double volatility_;
	double price_;
	double riskRate_;
	double expiration_; //convert to percent of year
	double strikePrice_;
	std::string optionType_;
	



	//Options();

	Options() //constructor 
		: volatility_(0.0), price_(0.0), riskRate_(0.0), expiration_(0.0),
		strikePrice_(0.0), optionType_("call") {};

	

	//------------getters--------------//

	// Time complexity: O(1) - gets the volatility value  
	// Space complexity: O(1)
	double getVoltaility(); 

	// Time complexity: O(1) - gets the current stock price value  
	// Space complexity: O(1)
	double getPrice();

	// Time complexity: O(1) - gets the risk rate value  
	// Space complexity: O(1)
	double getRiskRate();

	// Time complexity: O(1) - gets the expiration date value  
	// Space complexity: O(1)
	double getExpirationDate();

	// Time complexity: O(1) - gets the strike price value  
	// Space complexity: O(1)
	double getStrikePrice();

	// Time complexity: O(1) - gets the option type value  
	// Space complexity: O(1)
	std::string getOptionType();

	//---setters----------//

	// Time complexity: O(1) - sets the volaility value  
	// Space complexity: O(1)
	void setVoltaility(double v);

	// Time complexity: O(1) - sets the price value  
	// Space complexity: O(1)
	void setPrice(double s);

	// Time complexity: O(1) - sets the risk rate value  
	// Space complexity: O(1)
	void setRiskRate(double r);

	// Time complexity: O(1) - sets the expiration value  
	// Space complexity: O(1)
	void setExpirationDate(double ex);

	// Time complexity: O(1) - sets the strike price value  
	// Space complexity: O(1)
	void setStrikePrice(double st);

	// Time complexity: O(1) - sets the option type value  
	// Space complexity: O(1)
	void setOptionType(std::string val);
	

	// Time complexity: O(1) - changes time to percent of year   
	// Space complexity: O(1)
	void changeTime(double time);

};




#endif