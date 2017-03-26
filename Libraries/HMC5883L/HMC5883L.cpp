/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
----------------------
HMC5883L.cpp
Updated on 18/02/2017
----------------------
Implemented 
functions:

class HMC5883L{
constructor method
init
getRotationAngle
setAddress
}
---------------------
*/

#include "Arduino.h"
#include "Wire.h"
#include "HMC5883L.h"
/*
Constructor method
----------------------
class HMC883L
----------------------
Arguments:

int address
The preset i2c address
for the sensor.
(Set to
"HMC5883L_DEFAULT
_ADDRESS" if in
factory setup.)
----------------------
Description:
Sets up the
sensorAddress and
startingAngle class
variables to the
argument and to
magnetic North
respectively as initial
values.
*/
HMC5883L::HMC5883L(int address){
	sensorAddress=address;
	startingAngle=0.0f;
	
}
/*
void init
----------------------
class HMC883L
----------------------
Access: public
----------------------
Description:
Begins the i2c bus's
tasks in its standard
mode.
*/
void HMC5883L::init(){
	// Activate sensor
	Wire.beginTransmission(sensorAddress);
	//set rate to 75Hz
	Wire.write(0x02);
	Wire.write(0x00);
	Wire.endTransmission();
}
/*
float getAngle
----------------------
class HMC883L
----------------------
Access: public
----------------------
Description:
Returns a degree angle
using startingAngle as
the sensor front.
*/
float HMC5883L::getAngle(){
	// Read values and substract them from inital angle
	float angle=startingAngle-getRotationAngle();
	
	// Setup exclusively positive angles
	if(angle>=360.0f){
		angle-=360.0f;
	}
	if(angle<0.0f){
		angle+=360.0f;
	}

	return angle;
}
/*
void setStartingAngle
----------------------
class HMC883L
----------------------
Access: public
----------------------
Description:
Returns offset angle
to magnetic North in
degrees.
*/
float HMC5883L::getRawAngle(){
	// Get angle without filtering
	float angle=getRotationAngle();
	return angle;
}
/*
float getRotationAngle
----------------------
class HMC883L
----------------------
Access: private
----------------------
Description:
returns a degree angle
int ype float for the
current magnetic North
offset angle.
*/
float HMC5883L::getRotationAngle(){
	// Request the sensor values
	Wire.beginTransmission(sensorAddress);
	Wire.write(0x03);
	Wire.endTransmission();
	Wire.requestFrom(sensorAddress,6);
	
	// Reading sensor values and storing them in an array
	int values[6];
	while(Wire.available()<6);
	for(int i=0;i<6;i++){
		values[i]=Wire.read();
	}
	// Sort the bytes to the 3 axis variables
	float x=(int16_t)(values[1]|(int16_t)values[0]<<8);
	float y=(int16_t)(values[5]|(int16_t)values[4]<<8);
	float z=(int16_t)(values[3]|(int16_t)values[2]<<8);
	
	// Atan2 function for degree regression in radians
	float angle=(float)atan2(x,y);
	if(angle<0.0f){
		angle+=PI*2.0f;
	}
	if(angle>PI*2.0f){
		angle-=PI*2.0f;
	}
	// Convert angle from radians to degrees
	angle=(angle*180.0f)/PI;
	return angle;
}
/*
void setStartingAngle
----------------------
class HMC883L
----------------------
Access: public
----------------------
Description:
recalibrates
startingAngle to the
current offset angle
to magnetic North
to set the current
angle as the sensor
front angle
*/
void HMC5883L::setStartingAngle(){
	// Recalibrate the base angle
	startingAngle=getRotationAngle();
}