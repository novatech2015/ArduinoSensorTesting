#include <Wire.h> //I2C library
#include <HMC5883L.h>

HMC5883L hmc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  hmc.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tHeading\tXAxis\tYAxis\tZAxis");
}

void loop() {
  hmc.read();
  double xAxis = hmc.getX();
  double yAxis = hmc.getY();
  double zAxis = hmc.getZ();
  double heading = hmc.getHeading();
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
