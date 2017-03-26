/*
Developed by:
 _______  __    __  _____ 		 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
-----------------------
LightSensorBar.h
Updated on 19/02/2017
-----------------------
Description:
Made for RCJ Soccer
Open League
Refer to the Light
Sensor Bar design for
more information
-----------------------
class
Functions:

public:
	calibrate
	getLineDirection
	printRawInput
	printFilteredInput
-----------------------
*/
#ifndef LightSensorBar_h
#define LightSensorBar_h
#define DEFAULT_TOLERANCE 8
#define DEFAULT_TOLERANCE_OFFSET 0
class LightSensorBar{
	private:
		int tolerance;

		int offsetPort;
		int filterInput[6];

		bool autoCalibrate;
	public:
		LightSensorBar(int offsetAPort, int toleranceValue);
		char getLineDirection();
		void calibrate();
		void printRawInput();
		void printFilteredInput();
};
class CalibratedLightSensorBar{
	private:
		int toleranceOffset;

		int offsetPort;
		int filterInput[6];

		bool autoCalibrate;

		int highestValue[6];
		int lowestValue[6];
	public:
		CalibratedLightSensorBar(int offsetAPort,int toleranceOffsetValue);
		char getLineDirection();
		void calibrate();
		void printRawInput();
		void printFilteredInput();
};
#endif