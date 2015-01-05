#include "Arduino.h"
#include "Wire.h"
#include "HMC5883L.h"
#include "math.h"


void HMC5883L::begin(){
   _xAxis = 0;
   _yAxis = 0;
   _zAxis = 0;
   Wire.beginTransmission(0x1E);//Compass Address
   Wire.write(0x00);
   Wire.write(0x70);//Configures the BW_Rate to operate at 15 Hertz
   Wire.write(0x01);
   Wire.write(0x20);//Configures the DATA_FORMAT to operate with a range of +/- 1.3 Gauss
   Wire.write(0x02);
   Wire.write(0x00);//Configures the POWER_CTL to start measuring continuously
   Wire.endTransmission();
}

void HMC5883L::read(){
  Wire.beginTransmission(0x1E);
  Wire.write(0x03);
  Wire.requestFrom(0x1E, 6);
  int buffer[6];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  Wire.endTransmission();
  
  _xAxis = (buffer[0] << 8) | (buffer[1] & 0xff);
  _yAxis = (buffer[2] << 8) | (buffer[3] & 0xff);
  _zAxis = (buffer[4] << 8) | (buffer[5] & 0xff);  
}

double HMC5883L::getX(){
  return _xAxis * 0.004; 
}

double HMC5883L::getY(){
  return _yAxis * 0.004; 
}

double HMC5883L::getZ(){
  return _zAxis * 0.004; 
}

double HMC5883L::getHeading(){
  return atan2(_yAxis,_xAxis)*180/PI;
}
