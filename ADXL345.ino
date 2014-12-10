#include <Wire.h> //I2C library

double x_axisAccel = 0.0, y_axisAccel = 0.0, z_axisAccel = 0.0;
double kGsPerLSB = 1;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(5000);
  initAccel();
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tXAxis\tYAxis\tZAxis");
}

void loop() {
  read();
  double xAxis = getX();
  double yAxis = getY();
  double zAxis = getZ();
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(xAxis);
  Serial.print("\t");
  Serial.print(yAxis);
  Serial.print("\t");
  Serial.print(zAxis);
}

void initAccel(){
   Wire.beginTransmission(0x53);//Accel Address
//   Wire.write(0x2C);
//   Wire.write(0x08);//Configures the BW_Rate to operate at 25 Hertz
//   Wire.write(0x31);
//   Wire.write(0x0B);//Configures the DATA_FORMAT to operate in FULL_RES with a range of +/- 16g
   Wire.write(0x2D);
   Wire.write(0x08);//Configures the POWER_CTL to start measuring
   Wire.endTransmission();
}

void read(){
  Wire.beginTransmission(0x9d);
  Wire.write(0x32);
  Wire.requestFrom(0x9d, 6);
  int buffer[6];
  int bufferNumber = 0;
  
  while(Wire.available()){
    buffer[bufferNumber] = Wire.read();
    bufferNumber++;
  }
  Wire.endTransmission();
  
  x_axisAccel = ((buffer[1] << 8) & 0xff00) | (buffer[0] & 0xff);
  y_axisAccel = ((buffer[3] << 8) & 0xff00) | (buffer[2] & 0xff);
  z_axisAccel = ((buffer[5] << 8) & 0xff00) | (buffer[4] & 0xff);  
}

double getX(){
  return x_axisAccel; 
}

double getY(){
  return y_axisAccel; 
}

double getZ(){
  return z_axisAccel; 
}
