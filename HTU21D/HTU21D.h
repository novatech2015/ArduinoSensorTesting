#ifndef HTU21D_h
#define HTU21D_h

#include "Arduino.h"
#include "Wire.h"

class HTU21D {
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
