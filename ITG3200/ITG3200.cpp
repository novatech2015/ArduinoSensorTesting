#include "Arduino.h"
#include "Wire.h"
#include "ITG3200.h"


void ITG3200::begin(){
   _xAxis = 0;
   _yAxis = 0;
   _zAxis = 0;
   _heading = 0;
   _kLSBpDpS = 14.375;
   Wire.beginTransmission(0x68);//address for breakout
   Wire.write(0x3E); //POWER_CTL to start measuring
   Wire.write(0x00);
//   Wire.write(0x16); //FULL_RES, +-2000 deg/s blah blah
//   Wire.write(0x1C);
//   Wire.write(0x15); //SMPLRT_DIV to operate at 25 Hertz
//   Wire.write(0x27);
   Wire.endTransmission();
}

void ITG3200::read(){
  Wire.beginTransmission(0x68);
  Wire.write(0x1D);
  Wire.requestFrom(0x68, 6);
  int buffer[6];
  int bufferNumber = 0;
  	  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  Wire.endTransmission();
  	
  _xAxis = ((buffer[0] << 8)) | (buffer[1]);
  _yAxis = ((buffer[2] << 8)) | (buffer[3]);
  _zAxis = ((buffer[4] << 8)) | (buffer[5]);
  _heading += getZ() * 0.04;
}

double ITG3200::getX(){
  return (double) _xAxis / _kLSBpDpS;
}

double ITG3200::getY(){
  return (double) _yAxis / _kLSBpDpS;
}

double ITG3200::getZ(){
  return (double) _zAxis / _kLSBpDpS;
}

double ITG3200::getHeading(){
  return _heading;
}
