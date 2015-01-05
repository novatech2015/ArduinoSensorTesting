#ifndef BMP180_h
#define BMP180_h

#include "Arduino.h"
#include "Wire.h"

class BMP180 {
	public:
		void begin();
		void read();
		void readPressure();
		void readTemp();
		double getTemp();
		double getPressure();
		void setTemp(double temp);
	private:
		int readInt(char address);
		unsigned int readUInt(char address);
		double _temperature;
		double _pressure;
		int _AC1, _AC2, _AC3, _B1, _B2, _MB, _MC, _MD;
		unsigned int _AC4, _AC5, _AC6;
		long _X1, _X2, _X3, _B3, _B5, _B6;
		double _c3, _c4, _b1, _c5, _c6, _mc, _md, _x0, _x1, _x2, _y0, _y1, _y2, _p0, _p1, _p2;
		unsigned long _B4, _B7;

};

#endif
