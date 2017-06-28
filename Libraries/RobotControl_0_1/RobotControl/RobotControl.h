/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
--------------------------
RobotControl.h
Updated on 28/05/2017
--------------------------
Description:
Made for RCJ Soccer Open
League.
This library is meant to
include all control
systems in our robot.
--------------------------
Constant values:

MA-B-C-D constant values
that determine the motors
that are being used.
Example: MA+MB+MC given as
an argument for mts in
function setMotors will
only act on motors A,B
& C from the robot.
(See default motor
assignment order from line
71 thru 82.)
--------------------------
*/
#ifndef RobotControl_h
#define RobotControl_h
#define MA 1
#define MB 2
#define MC 3
#define MD 4
#include "Arduino.h"
#include "HMC5883L.h"
class VNHMotor{
	private:
		bool inv;
		unsigned int pwPort;
		unsigned int port1;
		unsigned int port2;
		unsigned int enPort;
		unsigned int maxPw;
	public:
		// Constructor method: "motorPort1" and "motorPort2" are the direction control ports in the VNH
		// series motor controllers, "power" is the PWM input port from the motor controller,
		// "enablePort" is the value for the pin connected to the EN input port on the motor controller,
		// "max power" (ranged from 0-255) will be the maximum power at which the motors will be able to run,
		// & "inverted" allows to invert the use of the digital ports set by "motorPort1" & "motorPort2"
		// (for which you may also swap their values if you wish to have the same effect).
		VNHMotor(int powerPort,int motorPort1,int motorPort2,int enablePort,int maxPower,bool inverted);
		
		// void set: Void sets the motor's power to the one specified in argument "power" (scaled from
		// -100.0 to 100.0 using the max power attribute in the constructor method.)
		void set(double power);
		
		// void setupMotors: "setupMotors" will set all pins specified in the constructor method to output
		// mode. This simplifies the lines of code required to set the modes each pin to OUTPUT.
		void setupMotor();

		// Sets the motor's power to 0.
		void stopMotor();
};
/*
Default motor assignment order:
	 
	 Frontal field of view
		\     ^     /
		 \   /|\   /
		  \ / | \ /
		   \  |  /
		    _ O _
		   /C\_/A\
Robot	  |---O---|
		   \D_|_B/
*/
class RobotControl{
	private:
		HMC5883L* magnetometer;
		VNHMotor** motors;
		int mode;
		float* heading;
		double degreesToRadians(double degrees);
		double toAngle(double angle);
	public:
		// Constructor method(1): "motorA,B,C,& D" are the pointers for the instances of "VNHMotor"s in the specified
		// order of assignment described from line 71 thru 82, & "headingAddr" is a float pointer to be set for a float
		// variable that will be changed periodically to the HMC5883L's current heading angle.
		RobotControl(VNHMotor* motorA,VNHMotor* motorB,VNHMotor* motorC,VNHMotor* motorD,float* headingAddr);

		// Constructor method(2): "motorA,B,C,& D" are the pointers for the instances of "VNHMotor"s in the specified
		// order of assignment described from line 71 thru 82, & "robotMagnetometer" is the pointer to the instance
		// for the robot's HMC5883L magnetometer.
		RobotControl(VNHMotor* motorA,VNHMotor* motorB,VNHMotor* motorC,VNHMotor* motorD,HMC5883L* robotMagnetometer);

		// void setMotors: Sets the motors specified on "mts" to the scaled power from -100.0 to 100.0 given to "power".
		// To set multiple motors to the same power output, you can use the constants MA,B,C,& D like so:
		// MA+MB as an expresion given to argument "mts" will set both motor A & B to the same power.
		// (robot.setMotors(MA+MB, 100.0))
		void setMotors(unsigned int mts,double power);
		
		// void stopRobot: Sets all robot motors to power 0.0 (setMotors(MA+MB+MC+MD,0.0) will have the same effect)
		void stopRobot();


		/*
		For both "vectorMove" methods:
			
			Frontal field of view
			        0 degr
				\     ^     /
				 \   /|\   /
				  \ / | \ /
				   \  |  /
			        _ O _
			Robot  /C\_/A\
	      270 degr|---O---|90 degr
			       \D_|_B/		
			      180 degr
		*/
		// void vectorMove(1): Calling fucntion "vectorMove(1)" will move the robot to the specified direction on argument "movementAngle" (in degrees)
		// at the power specified on argument "power" while alligning the robot towards the front (the others team's goal).
		void vectorMove(double movementAngle,double power);
		// void vectorMove(2): Calling fucntion "vectorMove(1)" will move the robot to the specified direction on argument "movementAngle" (in degrees)
		// at the power specified on argument "power" while alligning the robot towards the front (the others team's goal) for the the time specified
		// on argument "ms" (in milliseconds).
		void vectorMove(double movementAngle,double power,unsigned int ms);
		
		

		void vectorMoveLocked(double movementAngle,double power,float lockedAngle);
		void vectorMoveLocked(double movementAngle,double power,float lockedAngle,unsigned int millis);
		
		// void moveFwd(1): equivalent to vectorMove(0.0, 'power').
		void moveFwd(double power);
		// void moveFwd(2): equivalent to vectorMove(0.0, 'power', 'millis').
		void moveFwd(double power,unsigned int millis);
		// void moveRev(1): equivalent to vectorMove(180.0, 'power').
		void moveRev(double power);
		// void moveRev(2): equivalent to vectorMove(180.0, 'power', 'millis').
		void moveRev(double power,unsigned int millis);
		// void moveRight(1): equivalent to vectorMove(90.0, 'power').
		void moveRight(double power);
		// void moveRight(2): equivalent to vectorMove(90.0, 'power', 'millis').
		void moveRight(double power,unsigned int millis);
		// void moveLeft(1): equivalent to vectorMove(270.0, 'power').
		void moveLeft(double power);
		// void moveLeft(2): equivalent to vectorMove(270.0, 'power', 'millis').
		void moveLeft(double power,unsigned int millis);
};
#endif