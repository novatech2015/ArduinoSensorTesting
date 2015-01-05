#include <Wire.h> //I2C library
#include <HIH6130.h>

HIH6130 hih;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  hih.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tTemperature\tHumidity");
}

void loop() {
  hih.read();
  double temp = hih.getTemp();
  double humidity = hih.getHumidity();
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print(humidity);
}

