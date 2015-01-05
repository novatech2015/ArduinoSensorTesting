#include "Arduino.h"
#include "Wire.h"
#include "HIH6130.h"


void HIH6130::begin(){
   _temperature = 0.0;
   _humidity = 0.0;
}

void HIH6130::read(){
  Wire.beginTransmission(0x27);
  Wire.endTransmission();

  delay(100);
  Wire.requestFrom(0x27, 4);
  int buffer[4];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  Wire.endTransmission();
  
  _humidity = (((buffer[0] << 8) & 0x3f00) | (buffer[1] & 0xff)) * 6.10e-3;
  _temperature = (((buffer[2] << 8) & 0xff00) | (buffer[3] & 0xff))*0.01007141549/4 - 40.0;
}

double HIH6130::getTemp(){
  return _temperature; 
}

double HIH6130::getHumidity(){
  return _humidity; 
}
