#ifndef ITG3200_h
#define ITG3200_h

#include "Arduino.h"
#include "Wire.h"
#include "math.h"

class ITG3200 {
	public:
		void begin();
		void read();
		double getX();
		double getY();
		double getZ();
		double getHeading();
	private:
		double _xAxis, _yAxis, _zAxis, _heading;
		double _kLSBpDpS;

};

#endif
