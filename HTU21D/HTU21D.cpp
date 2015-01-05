#include "Arduino.h"
#include "Wire.h"
#include "HTU21D.h"


void HTU21D::begin(){
   _temperature = 0.0;
   _humidity = 0.0;
}

void HTU21D::read(){
  Wire.beginTransmission(0x40);
  Wire.write(0xF3);
  Wire.endTransmission();
  delay(60);
  Wire.requestFrom(0x40, 2);
  int buffer[4];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }

  _temperature = -46.85 + (((((unsigned int)buffer[0] << 8) | buffer[1]) & 0xFFFC) / 65536.0 * 175.72);
  
  
  Wire.beginTransmission(0x40);
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(55);
  Wire.requestFrom(0x40, 2);
  bufferNumber = 2;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }

  _humidity = -6 + (((((unsigned int)buffer[2] << 8) | (unsigned int)buffer[3]) & 0xFFFC) / 65536.0 * 125);
  
}

double HTU21D::getTemp(){
  return _temperature; 
}

double HTU21D::getHumidity(){
  return _humidity; 
}
