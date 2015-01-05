#include "Arduino.h"
#include "Wire.h"
#include "TSL2561.h"


void TSL2561::begin(){
   _channel0 = 0;
   _channel1 = 0;
   _lux = 0;
   Wire.beginTransmission(0x39);//TSL Address
   Wire.write(0x01 | 0x80);
   Wire.write(0x0A);//Integration of 402 ms with a 1 : 1 scale factor with 1x gain.
   Wire.endTransmission(); 
   Wire.beginTransmission(0x39);//TSL Address
   Wire.write(0x00 | 0x80);
   Wire.write(0x03);//Power Up

   Wire.endTransmission();
}

void TSL2561::read(){
  Wire.beginTransmission(0x39);
  Wire.write(0x0C | 0x80);
  Wire.requestFrom(0x39, 4);
  int buffer[4];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  Wire.endTransmission();
  
  _channel0 = ((buffer[1] << 8) & 0xff00) | (buffer[0] & 0xff);
  _channel1 = ((buffer[3] << 8) & 0xff00) | (buffer[2] & 0xff);
}

unsigned short TSL2561::getChannel0(){
	return _channel0;
}

unsigned short TSL2561::getChannel1(){
	return _channel1;
}

double TSL2561::getLux(){
   
  double ratio, d0, d1;
  // Determine if either sensor saturated (0xFFFF)
  // If so, abandon ship (calculation will not be accurate)
  if ((_channel0 == 0xFFFF) || (_channel1 == 0xFFFF))
  {
  _lux = 0.0;
  return(false);
  }
  // Convert from unsigned integer to floating point
  d0 = _channel0; d1 = _channel1;
  // We will need the ratio for subsequent calculations
  ratio = d1 / d0;
  // Normalize for integration time
  d0 *= (402.0/402.0);
  d1 *= (402.0/402.0);
  // Determine _lux per datasheet equations:
  if (ratio < 0.5)
  {
  _lux = 0.0304 * d0 - 0.062 * d0 * pow(ratio,1.4);
  return(_lux);
  }
  if (ratio < 0.61)
  {
  _lux = 0.0224 * d0 - 0.031 * d1;
  return(_lux);
  }
  if (ratio < 0.80)
  {
  _lux = 0.0128 * d0 - 0.0153 * d1;
  return(_lux);
  }
  if (ratio < 1.30)
  {
  _lux = 0.00146 * d0 - 0.00112 * d1;
  return(_lux);
  } 
}



