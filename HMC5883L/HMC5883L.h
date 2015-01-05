#ifndef HMC5883L_h
#define HMC5883L_h

#include "Arduino.h"
#include "Wire.h"
#include "math.h"

class HMC5883L {
	public:
		void begin();
		void read();
		double getX();
		double getY();
		double getZ();
		double getHeading();
	private:
		double _xAxis, _yAxis, _zAxis;

};

#endif
