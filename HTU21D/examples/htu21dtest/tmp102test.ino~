#include <Wire.h> //I2C library
#include <TMP102.h>

TMP102 tmp;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  tmp.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tTemperature");
}

void loop() {
  tmp.read();
  double temp = tmp.getTemp();
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(temp);
}

