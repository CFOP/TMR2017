#ifndef MotorControl_h
#define MotorControl_h
#define VNH_MOTOR_1 0
#define VNH_MOTOR_2 1
#define VNH_FWD 0
#define VNH_REV 1
#define VNH_STOP 2

#define ROBOT_MOTOR_A 1
#define ROBOT_MOTOR_B 2
#define ROBOT_MOTOR_C 3
#define ROBOT_MOTOR_D 4


int absolute(int val);
class VNH5019{
	private:
		bool enabled[2];
		int portsMap[4][2];
	public:
		VNH5019(int enPorts[2],int pwmPorts[2],int m1Ports[2],int m2Ports[2]);
		void enableShield();
		void disableShield();

		void setMotor(int motor,unsigned int pw,int direction);
		void stopMotor(int motor);
		void enableMotor(int motor);
		void disableMotor(int motor);
		bool isEnabled(int motor);
};
/*
 FRONT
   ^
  _|_
 /A C\
|--O--|
 \B_D/
*/
 
class RobotMotors{
	private:
		VNH5019* motorsAB;
		VNH5019* motorsCD;
	public:
		RobotMotors(int enPorts[4],int pwmPorts[4],int m1Ports[4],int m2Ports[4],bool inverted[4]);
		void setMotors(int motors,int pw);
};
class RobotControl{
	private:
		RobotMotors* robotMotors;
		int scale;
	public:
		RobotControl(RobotMotors* motors,int pwScale);
		void vectorMove(float angle,int maxSpeed);
		void moveFwd(int speed);
		void moveRev(int speed);
		void moveLeft(int speed);
		void moveRight(int speed);
		void turnLeft(int speed);
		void turnRight(int speed);
};
#endif