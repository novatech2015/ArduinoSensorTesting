#include "Arduino.h"
#include "MCP3008.h"

MCP3008::MCP3008(int sclk,int miso,int mosi,int cs0){
	_sclk = sclk;
	_miso = miso;
	_mosi = mosi;
	_cs0 = cs0;
  pinMode(_sclk, OUTPUT);
  pinMode(_miso, INPUT);
  pinMode(_mosi, OUTPUT);
  pinMode(_cs0, OUTPUT);
}

void MCP3008::begin(){

}

int MCP3008::readChannel(int channel){
 int output = 0;
 int i;
 int inputArray[5]; 
 
 if(channel < 0 || channel > 7){
  return -1; 
 }
 digitalWrite(_cs0, HIGH);
 digitalWrite(_sclk, LOW);
 digitalWrite(_cs0, LOW);
 mcp3008_select_chip(inputArray, channel);
 for(i=0; i<5; i++){
  clocked_write(inputArray[i]);
 }
 for(i = 12; i>0; i--){
   if(clocked_read() == 1){
     output += power_of_2(i);
     }
 }
 digitalWrite(_cs0, HIGH);
 output /= 4;
 return output;
}

void MCP3008::mcp3008_select_chip(int bin[], int channel){
  bin[0] = 1; bin[1] = 1;
  int i = 2;
  int o[3];
  for(i=2; i >= 0; i--){
  o[i] = (channel % 2);
  channel /= 2;
  }
  int c;
  for (c = i-1; c>=0; c--){
  o[c] = 0;
  }
  c = 2;
  for( i = 0; i<3; i++){
  bin[c] = o[i];
  c++;
  }
}

int MCP3008::power_of_2(int exp){
  int output = 1;
  int i;
  for (i = 1; i<=exp; i++) {
  output *= 2;
  }
  return output;
}

void MCP3008::clocked_write(int value){
  if(value == 1){
    digitalWrite(_mosi, HIGH);
  }else if(value == 0){
    digitalWrite(_mosi, LOW);
  }else{
    Serial.println("ERROR!!!!!!");
  }
  digitalWrite(_sclk, HIGH);
  digitalWrite(_sclk, LOW);
}

int MCP3008::clocked_read(){
  digitalWrite(_sclk, HIGH);
  digitalWrite(_sclk, LOW);
  return digitalRead(_miso);
}
