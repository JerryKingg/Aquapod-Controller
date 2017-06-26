/*
 * Thermometer.cpp
 *
 *  Created on: Jun 15, 2017
 *      Author: james
 */

#include <vector>
#include <cmath>
#include "wiringPi.h"
#include "Thermometer.h"
#include <iostream>

using namespace std;

namespace Aquapod {


	Thermometer::Thermometer()
	{
		capacitor = 0.000001;
		resistor = 10000;
		alpha =.001344668;
		beta = .000207173;
		gamma =.000000145796;
		measurePin = 24;
		chargePin = 25;

		if (wiringPiSetupGpio())
		{

		pinMode(measurePin, OUTPUT);
		pinMode(chargePin, OUTPUT);

		digitalWrite(measurePin,0);
		digitalWrite(chargePin,0);

		} else
		{
			cout << "setup failed with return code 0!";
		}
	}

	Thermometer::Thermometer(long double cap, long double res)
	{
		capacitor = cap;
		resistor = res;
		alpha =.001344668;
		beta = .000207173;
		gamma =.000000145796;
		measurePin = 24;
		chargePin = 25;

		if (wiringPiSetupGpio())
		{

		pinMode(measurePin, OUTPUT);
		pinMode(chargePin, OUTPUT);

		digitalWrite(measurePin,0);
		digitalWrite(chargePin,0);

		} else
		{
			cout << "setup failed with return code 0!";
		}
	}


	Thermometer::Thermometer(long double cap, long double res, int cpin, int mpin)
	{
		capacitor = cap;
		resistor = res;
		alpha =.001344668;
		beta = .000207173;
		gamma =.000000145796;
		measurePin = cpin;
		chargePin = mpin;

		pinMode(measurePin, OUTPUT);
		pinMode(chargePin, OUTPUT);

		digitalWrite(measurePin,0);
		digitalWrite(chargePin,0);
	}

	Thermometer::Thermometer(long double cap, long double res, long double a, long double b, long double c)
	{
		capacitor = cap;
		resistor = res;
		alpha = a;
		beta = b;
		gamma = c;
		measurePin = 24;
		chargePin = 25;

		if (wiringPiSetupGpio())
		{

		pinMode(measurePin, OUTPUT);
		pinMode(chargePin, OUTPUT);

		digitalWrite(measurePin,0);
		digitalWrite(chargePin,0);

		} else
		{
			cout << "setup failed with return code 0!";
		}
	}

	Thermometer::Thermometer(long double cap, long double res, long double a, long double b, long double c, int cpin, int mpin)
	{
		capacitor = cap;
		resistor = res;
		alpha = a;
		beta = b;
		gamma = c;
		measurePin = cpin;
		chargePin = mpin;

		pinMode(measurePin, OUTPUT);
		pinMode(chargePin, OUTPUT);

		digitalWrite(measurePin,0);
		digitalWrite(chargePin,0);
	}

	double Thermometer::measureChargeTime()
	{
		unsigned int startTime;
		unsigned int endTime;

		long double chargeTime;


		pinMode(measurePin, INPUT);
		pullUpDnControl(measurePin, PUD_OFF);
		pinMode(chargePin, OUTPUT);

		startTime = micros();
		digitalWrite(chargePin, 1);

		while(!( digitalRead(measurePin) ))
		{
			//keep polling
		}

		endTime = micros();

		chargeTime = 0.000001 * (endTime - startTime);

		return chargeTime;
	}

	double Thermometer::measureResistance()
	{
		//t = r*c so r = t/c
		double thermistorResistance = Thermometer::measureChargeTime()/capacitor;
		//subtract the resistance of the series resistor
		thermistorResistance -= resistor;

		return thermistorResistance;
	}


	double Thermometer::measureTemperature()
	{
		double resistance = Thermometer::measureTemperature();
		//stienhart-hart equation gives the reciprocal of temperature 1/Temp = A + B*ln(R) + C*(ln(R)^3)
		long double recipTemp = alpha + (beta * log(resistance)) + (gamma * pow( log(resistance), 3.0));

		return 1/recipTemp;
	}


	Thermometer::~Thermometer()
	{
	// TODO Auto-generated destructor stub
	}




} /* namespace Aquapod */
