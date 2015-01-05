#include <Wire.h> //I2C library
#include <BMP180.h>

BMP180 bmp;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  bmp.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tTemperature\tPressure");
}

void loop() {
  bmp.readPressure();
  bmp.setTemp(22.10);
  double temp = bmp.getTemp();
  double pressure = bmp.getPressure();
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print(pressure);
  delay(300);
}

