#include "Arduino.h"
#include "Wire.h"
#include "HTInfraredSeeker.h"

void HTInfraredSeeker::init(){
	Wire.begin();
  	Wire.beginTransmission(HTInfraredSeeker::Address);
  	Wire.write(0x00);
  	Wire.endTransmission();
}
void HTInfraredSeeker::readValues(byte OffsetAddress, byte* buffer){
	HTInfraredSeeker::init();
	Wire.beginTransmission(HTInfraredSeeker::Address);
	Wire.write(OffsetAddress);
	Wire.endTransmission();
	Wire.requestFrom(HTInfraredSeeker::Address, 6);
	for(byte i = 0; i < 6; i++){
		buffer[i] = Wire.read();
	}
	while(Wire.available()>0)
		Wire.read();
	Wire.endTransmission();
}
InfraredInput HTInfraredSeeker::sortValues(byte* buffer){
	InfraredInput data;
	data.direction = buffer[0];
	data.strength1=buffer[1];
	data.strength2=buffer[2];
	data.strength3=buffer[3];
	data.strength4=buffer[4];
	data.strength5=buffer[5];
	data.strengthAll=0;
	for(int i=1;i<6;i++){
		if(buffer[i]>data.strengthAll){
			data.strengthAll=buffer[i];
		}
	}
	return data;
}
InfraredInput HTInfraredSeeker::readSensorValues(){
	byte buffer[6];
	readValues(0x49,buffer);
	return sortValues(buffer);
}