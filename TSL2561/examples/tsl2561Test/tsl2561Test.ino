#include <Wire.h>
#include "TSL2561.h"

TSL2561 tsl;

void setup(){
  Serial.begin(9600);
  Wire.begin(); 
  tsl.begin();
  Serial.println(">>>>");
  Serial.println("Time\tData_0\tData_1\tm_lux");
}

void loop(){
  tsl.read();
  unsigned short lum0 = tsl.getChannel0();
  unsigned short lum1 = tsl.getChannel1();
  double lux = tsl.getLux();
  long time = millis();
  Serial.println();
  Serial.print(time);
  Serial.print("\t");
  Serial.print(lum0);
  Serial.print("\t");
  Serial.print(lum1);
  Serial.print("\t");
  Serial.print(lux); 
}
