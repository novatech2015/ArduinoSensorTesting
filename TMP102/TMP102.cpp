#include "Arduino.h"
#include "Wire.h"
#include "TMP102.h"


void TMP102::begin(){
	_temperature = 0;
}

void TMP102::read(){
	Wire.beginTransmission(0x48);
	Wire.write(0x00);
	Wire.requestFrom(0x48, 2);
	int buffer[2];
	int bufferNumber = 0;
  
	while(Wire.available()){
		buffer[bufferNumber] = Wire.read();
		bufferNumber++;
	}
	Wire.endTransmission();
	_temperature = buffer[0] + (0.0625 * (buffer[1]>>4));
}

double TMP102::getTemp(){
  return _temperature; 
}
