#include <Wire.h> //I2C library
#include <HTU21D.h>

HTU21D htu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  htu.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tTemperature\tHumidity");
}

void loop() {
  htu.read();
  double temp = htu.getTemp();
  double humidity = htu.getHumidity();
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print(humidity);
}

