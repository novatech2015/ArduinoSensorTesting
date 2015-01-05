#ifndef HIH6130_h
#define HIH6130_h

#include "Arduino.h"
#include "Wire.h"

class HIH6130 {
	public:
		void begin();
		void read();
		double getTemp();
		double getHumidity();
	private:
		double _temperature;
		double _humidity;

};

#endif
