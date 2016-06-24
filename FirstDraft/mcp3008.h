#ifndef __MCP3008__
#define __MCP3008__

// Init function. Must be just called once
void mcp3008Setup (int spiChannel);

// thread safe fcuntion to read from one of the 8 channels
int myAnalogRead(int analogChannel);

void mcp3008Close();

#endif
