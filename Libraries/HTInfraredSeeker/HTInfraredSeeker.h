#ifndef HTInfraredSeeker_h
#define HTInfraredSeeker_h
#include "Arduino.h"
	struct InfraredInput{
	  	byte direction;
	  	byte strength1;
		byte strength2;
		byte strength3;
		byte strength4;
		byte strength5;
		byte strengthAll;
	};
	class HTInfraredSeeker{
		public:
			static void init();
			static InfraredInput readSensorValues();
	  	private:
			static InfraredInput sortValues(byte* buffer);
			static void readValues(byte OffsetAddress, byte* buffer);
			static const int Address=0x10/2;
	};
#endif