#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{ 
   uint16_t b=pixy.getBlocks();
  Serial.println(b);
}

