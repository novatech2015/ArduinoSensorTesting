#ifndef MCP3008_h
#define MCP3008_h

#include "Arduino.h"

class MCP3008 {
	public:
		MCP3008(int sclk,int miso,int mosi,int cs0);
		void begin();
		int readChannel(int channel);
	private:
		void mcp3008_select_chip(int bin[], int channel);
		int power_of_2(int exp);
		void clocked_write(int value);
		int clocked_read();
		int _sclk, _miso, _mosi, _cs0;

};

#endif
