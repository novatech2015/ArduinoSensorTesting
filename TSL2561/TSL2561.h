#ifndef TSL2561_h
#define TSL2561_h

#include "Arduino.h"
#include "Wire.h"

class TSL2561 
{
	public:
		void begin();
		void read();
		unsigned short getChannel0();
		unsigned short getChannel1();
		double getLux();
	private:
		unsigned short _channel0, _channel1;
		double _lux;

};

#endif
