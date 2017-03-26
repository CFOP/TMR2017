/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
--------------------------
HMC5883L.h
Updated on 18/02/2017
--------------------------
Description:
Made for RCJ Soccer Open
League.
This library is meant to
meassure the relative
rotation of a robot using
a magnetometer.
--------------------------
Constant values:

HMC5883L_DEFAULT_ADDRESS
Constant for
magnetometer's default
i2c address


class HMC5883L{
Functions:

private:
	float getRotationAngle
public:
	constructor method
	void init
	void setStartingAngle
	float getAngle
	float getRawAngle

}
--------------------------
*/
#ifndef HMC5883L_h
#define HMC5883L_h
#define HMC5883L_DEFAULT_ADDRESS 0x1E
class HMC5883L{
	private:
		int sensorAddress;
		float startingAngle;
		float getRotationAngle();
	public:
		/*
		Constructor method: sets the initial i2c address for the sensor 
		and sets the initial rotation angle based on magnetic north.
		method args: i2c address
		*/
		HMC5883L(int address);
		
		void init();
		/*
		reset angle method: resets the initial rotation angle
		method args: none
		*/
		void setStartingAngle();
		float getAngle();
		float getRawAngle();
};
#endif