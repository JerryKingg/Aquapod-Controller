/*
 * Thermometer.h
 *
 *  Created on: Jun 15, 2017
 *      Author: james
 */
#include "wiringPi.h"

#ifndef THERMOMETER_H_
#define THERMOMETER_H_

namespace Aquapod {

class Thermometer {

private:

	//pins
	int measurePin;
	int chargePin;

	//capacitance in farads
	long double capacitor;
	//resistance of the series resistor in ohms
	long double resistor;

	//steinhart-hart coefficients
	long double alpha;
	long double beta;
	long double gamma;

public:
	Thermometer();
	Thermometer(long double cap, long double res);
	Thermometer(long double cap, long double res, int cpin, int mpin);
	Thermometer(long double cap, long double res, long double a, long double b, long double c);
	Thermometer(long double cap, long double res, long double a, long double b, long double c, int cpin, int mpin);
	double measureChargeTime();
	double measureResistance();
	double measureTemperature();
	virtual ~Thermometer();
};

} /* namespace Aquapod */

#endif /* THERMOMETER_H_ */
