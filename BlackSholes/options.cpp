#include "options.h"


//Getter and Setter functions only------------------//

//All fucntions are O(n) runtime and space complexity


double Options::getVoltaility()
{
	return volatility_;
}

double Options::getPrice()
{
	return price_;
}

double Options::getRiskRate()
{
	return riskRate_;
}

double Options::getExpirationDate()
{
	return expiration_;
}

double Options::getStrikePrice()
{
	return strikePrice_;
}

std::string Options::getOptionType()
{
	return optionType_;
}




void Options::setVoltaility(double v)
{
	volatility_ = v;
}

void Options::setPrice(double newPrice)
{
	price_ = newPrice;
}

void Options::setRiskRate(double rate)
{
	riskRate_ = rate;
}

void Options::setExpirationDate(double time)
{
	expiration_ = time;
}

void Options::setStrikePrice(double strike) {
	strikePrice_ = strike;
}


void Options::setOptionType(std:: string val)
{
	optionType_ = val;
}



void Options::changeTime(double time)
{
	return;
}