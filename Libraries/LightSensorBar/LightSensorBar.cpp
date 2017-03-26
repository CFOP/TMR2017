/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
----------------------
LightSensorBar.h
Updated on 19/02/2017
---------------------- 
class LightSensorBar{
Implemented 
functions:

constructor method
calibrate
getLineDirection
printRawInput
printFilteredInput
}
----------------------
*/
#include "Arduino.h";
#include "LightSensorBar.h";

/*
Constructor method
----------------------
Arguments:

int offsetAPort
All photoresistors are
expected to have
adjacent analog  input
port connections. This
argument is used to 
specify where the
range of analog ports
begins.
----------------------
Description:
Sets the offsetPort
variable to the
start of the analog
port range.
*/

LightSensorBar::LightSensorBar(int offsetAPort, int toleranceValue){
	tolerance=toleranceValue;
	offsetPort=offsetAPort;
}
/*
char getLineDirection
----------------------
class LightSensorBar
----------------------
Access: public
----------------------
Description:
Returns a character
indicating the
relative position of
the line under the
robot to the sensor
bar. (Character r
for right, l for left,
m for middle, and n
for none.)
*/
char LightSensorBar::getLineDirection(){
	for(int i=0;i<2;i++){
		if(analogRead(offsetPort+3+i)>filterInput[3+i]+tolerance){
			return 'm';
		}
	}
	for(int i=0;i<3;i++){
		if(analogRead(offsetPort+i)>filterInput[i]+tolerance){
			return 'l';
		}
	}
	for(int i=0;i<3;i++){
		if(analogRead(offsetPort+5+i)>filterInput[5+i]+tolerance){
			return 'r';
		}
	}
	return 'n';
}
/*
void printRawInput
----------------------
class LightSensorBar
----------------------
Access: public
----------------------
Description:
Prints all
photoresistor analog
port raw readings.
*/
void LightSensorBar::printRawInput(){
	for(int i=0;i<8;i++){
		Serial.print((String)analogRead(offsetPort+i)+"\t");
	}
	Serial.println();
}
/*
void printFilteredInput
-----------------------
class LightSensorBar
-----------------------
Access: public
-----------------------
Description:
Prints a value for
every photoresistor
that specifies if the
current photoresistor
is detecting the white
line or not (,printing
Y for yes and N for no)
*/
void LightSensorBar::printFilteredInput(){
	for(int i=0;i<8;i++){
		if(analogRead(offsetPort+i)>filterInput[i]+tolerance){
			Serial.print("Y");
		}
		else{
			Serial.print("N");
		}
		Serial.print('\t');
	}
	Serial.println();
}

void LightSensorBar::calibrate(){
	for(int i=0;i<8;i++){
		filterInput[i]=analogRead(offsetPort+i);
	}
}
/*






















/*
TODO
*/

CalibratedLightSensorBar::CalibratedLightSensorBar(int offsetAPort,int toleranceOffsetValue){
	offsetPort=offsetAPort;
	toleranceOffset=toleranceOffsetValue;
	for(int i=0;i<8;i++){
		highestValue[i]=0;
		lowestValue[i]=1023;
	}
}


char CalibratedLightSensorBar::getLineDirection(){
	for(int i=0;i<2;i++){
		if(analogRead(offsetPort+3+i)>(lowestValue[3+i]+highestValue[3+i])/2+toleranceOffset){
			return 'm';
		}
	}
	for(int i=0;i<3;i++){
		if(analogRead(offsetPort+i)>(lowestValue[i]+highestValue[i])/2+toleranceOffset){
			return 'l';
		}
	}
	for(int i=0;i<3;i++){
		if(analogRead(offsetPort+5+i)>(lowestValue[5+i]+highestValue[5+i])/2+toleranceOffset){
			return 'r';
		}
	}
	return 'n';
}

/*

void calibrate
----------------------
class LightSensorBar
----------------------
Access: public
----------------------
Description:
Sets the current
photoresistor readings
as the green color
readings. The
calibration is
individual, since the
readings may vary
between the
photoresistors because
of positioning and
manufacturing reasons.
*/
void CalibratedLightSensorBar::calibrate(){
	int in;
	for(int i=0;i<8;i++){
		in=analogRead(offsetPort+i);
		if(in>highestValue[i]){
			highestValue[i]=in;
		}
		if(in<lowestValue[i]){
			lowestValue[i]=in;
		}
	}
}
/*
void printRawInput
----------------------
class LightSensorBar
----------------------
Access: public
----------------------
Description:
Prints all
photoresistor analog
port raw readings.
*/
void CalibratedLightSensorBar::printRawInput(){
	for(int i=0;i<8;i++){
		Serial.print((String)analogRead(offsetPort+i)+"\t");
	}
	Serial.println();
}
/*
void printFilteredInput
-----------------------
class LightSensorBar
-----------------------
Access: public
-----------------------
Description:
Prints a value for
every photoresistor
that specifies if the
current photoresistor
is detecting the white
line or not (,printing
Y for yes and N for no)
*/
void CalibratedLightSensorBar::printFilteredInput(){
	for(int i=0;i<8;i++){
		if(analogRead(offsetPort+i)>(lowestValue[i]+highestValue[i])/2+toleranceOffset){
			Serial.print("Y");
		}
		else{
			Serial.print("N");
		}
		Serial.print('\t');
	}
	Serial.println();
}