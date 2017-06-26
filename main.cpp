#include<iostream>
#include"Thermometer.h"
#include<vector>
#include"wiringPi.h"

int main()
{



	long double cap;
	long double res;

	int chargePin;
	int measurePin;

	bool breaker = true;

	std::vector<double> falseDatabase;

	Aquapod::Thermometer thermoscope = Aquapod::Thermometer(cap, res, chargePin, measurePin);

	while(breaker)
	{
		std::cout << "type 1 to measure the temperature, or 0 to exit:\n";
		std::cin >> breaker;

		if(breaker)
		{
			falseDatabase.push_back(thermoscope.measureTemperature());
			for(int i=0; i<falseDatabase.size(); i++)
			{
				std::cout << "Temp #" << i+1 << ": " << falseDatabase[i] << std::endl;
			}
		}

	}

return 0;
}
