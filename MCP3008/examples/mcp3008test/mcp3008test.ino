#include <MCP3008.h>

int sclk = 9;
int miso = 10;
int mosi = 11;
int cs0  = 12;
MCP3008 mcp(sclk,miso,mosi,cs0);

void setup() {
  Serial.begin(9600);
  mcp.begin();
  delay(100);
  Serial.println(">>>>>>>>>>>>>>>>>>>");
  Serial.println("Time\tChannel 0");
}

void loop() {
  int channel0 = mcp.readChannel(0);
  long   time  = millis(); 
  Serial.println(); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(channel0);
}

