#include "Arduino.h"
#include "Wire.h"
#include "BMP180.h"


void BMP180::begin(){
   _temperature = 0;
   _pressure = 0;
   _AC1 = readInt(0xAA);
   _AC2 = readInt(0xAC);
   _AC3 = readInt(0xAE);
   _AC4 = readUInt(0xB0);
   _AC5 = readUInt(0xB2);
   _AC6 = readUInt(0xB4);
   _B1 = readInt(0xB6);
   _B2  = readInt(0xB8);
   _MB  = readInt(0xBA);
   _MC  = readInt(0xBC);
   _MD  = readInt(0xBE);
   
   
  _c3 = 160.0 * pow(2,-15) * _AC3;
  _c4 = pow(10,-3) * pow(2,-15) * _AC4;
  _b1 = pow(160,2) * pow(2,-30) * _B1;
  _c5 = (pow(2,-15) / 160) * _AC5;
  _c6 = _AC6;
  _mc = (pow(2,11) / pow(160,2)) * _MC;
  _md = _MD / 160.0;
  _x0 = _AC1;
  _x1 = 160.0 * pow(2,-13) * _AC2;
  _x2 = pow(160,2) * pow(2,-25) * _B2;
  _y0 = _c4 * pow(2,15);
  _y1 = _c4 * _c3;
  _y2 = _c4 * _b1;
  _p0 = (3791.0 - 8.0) / 1600.0;
  _p1 = 1.0 - 7357.0 * pow(2,-20);
  _p2 = 3038.0 * 100.0 * pow(2,-36);
  
}

void BMP180::read(){
	readTemp();
	readPressure();
}

void BMP180::readTemp(){
  Wire.beginTransmission(0x77);
  unsigned char bytes[2];
  bytes[0] = 0xF4;
  bytes[1] = 0x2E;
  Wire.write(bytes,2); 
  delay(5);
  int error = Wire.endTransmission();
  Wire.beginTransmission(0x77);
  Wire.write(0xF6);
  error = Wire.endTransmission();
  Wire.requestFrom(0x77, 2);
  unsigned char buffer[2];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }

  double tu = (buffer[0] * 256.0) + buffer[1];
  double a = _c5 * (tu - _c6);
  _temperature = a + (_mc / (a + _md));
}

void BMP180::readPressure(){
  Wire.beginTransmission(0x77);
  unsigned char bytes[2];
  bytes[0] = 0xF4;
  bytes[1] = 0xF4;
  Wire.write(bytes,2); 
  delay(26);
  int error = Wire.endTransmission();
  Wire.beginTransmission(0x77);
  Wire.write(0xF6);
  error = Wire.endTransmission();
  Wire.requestFrom(0x77, 3);
  unsigned char buffer[3];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  
  double s, x, y, z;
  double uncompensatedPressure = (buffer[0]*256.0) + buffer[1] + (buffer[2]/256.0);
  
  
  s = _temperature - 25.0;
  x = (_x2 * pow(s,2)) + (_x1 * s) + _x0;
  y = (_y2 * pow(s,2)) + (_y1 * s) + _y0;
  z = (uncompensatedPressure - x) / y;
  _pressure = (_p2 * pow(z,2)) + (_p1 * z) + _p0;
}

double BMP180::getTemp(){
  return _temperature; 
}

double BMP180::getPressure(){
  return _pressure; 
}

void BMP180::setTemp(double temp){
  _temperature = temp;
}

int BMP180::readInt(char address){
  Wire.beginTransmission(0x77);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(0x77, 2);
  int buffer[2];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  return (buffer[0]<<8)|(buffer[1]);
}

unsigned int BMP180::readUInt(char address){
  Wire.beginTransmission(0x77);
  Wire.write(address);
  int error = Wire.endTransmission();
  Wire.requestFrom(0x77, 2);
  int buffer[2];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  return (buffer[0]<<8)|(buffer[1]);
}
