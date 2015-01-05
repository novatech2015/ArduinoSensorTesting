#include <Wire.h> //I2C library
#include <ITG3200.h>

ITG3200 itg;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  itg.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tHeading\tXAxis\tYAxis\tZAxis");
}

void loop() {
  itg.read();
  double xAxis = itg.getX();
  double yAxis = itg.getY();
  double zAxis = itg.getZ();
  double heading = itg.getHeading();
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(heading);
  Serial.print("\t");
  Serial.print(xAxis);
  Serial.print("\t");
  Serial.print(yAxis);
  Serial.print("\t");
  Serial.print(zAxis);
}
