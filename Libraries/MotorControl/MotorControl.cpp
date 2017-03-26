#include "MotorControl.h"
#include "Arduino.h";
#include "math.h"
int absolute(int val){
	if(val<0)
		return -val;
	return val;
}
VNH5019::VNH5019(int enPorts[2],int pwmPorts[2],int m1Ports[2],int m2Ports[2]){
	portsMap[0][0]=enPorts[0];
	portsMap[0][1]=enPorts[1];

	portsMap[1][0]=pwmPorts[0];
	portsMap[1][1]=pwmPorts[1];

	portsMap[2][0]=m1Ports[0];
	portsMap[2][1]=m1Ports[1];

	portsMap[3][0]=m2Ports[0];
	portsMap[3][1]=m2Ports[1];
	disableShield();
}

void VNH5019::setMotor(int motor,unsigned int pw,int direction){
	if(direction==VNH_STOP){
		stopMotor(motor);
	}
	else{
		if(direction==VNH_FWD){
			analogWrite(portsMap[1][motor],pw);
			digitalWrite(portsMap[2+motor][0],HIGH);
			digitalWrite(portsMap[2+motor][1],LOW);
		}
		else{
			analogWrite(portsMap[1][motor],pw);
			digitalWrite(portsMap[2+motor][0],HIGH);
			digitalWrite(portsMap[2+motor][1],LOW);
		}
	}
}

void VNH5019::enableShield(){
	enableMotor(VNH_MOTOR_1);
	enableMotor(VNH_MOTOR_2);
}
void VNH5019::disableShield(){
	stopMotor(VNH_MOTOR_1);
	disableMotor(VNH_MOTOR_1);
	stopMotor(VNH_MOTOR_1);
	disableMotor(VNH_MOTOR_2);
}
void VNH5019::stopMotor(int motor){
	digitalWrite(portsMap[1][motor],LOW);
	digitalWrite(portsMap[2+motor][0],LOW);
	digitalWrite(portsMap[2+motor][1],LOW);
}
void VNH5019::disableMotor(int motor){
	digitalWrite(portsMap[0][motor],LOW);
	enabled[motor]=false;
}
void VNH5019::enableMotor(int motor){
	digitalWrite(portsMap[0][motor],HIGH);
	enabled[motor]=true;
}
bool VNH5019::isEnabled(int motor){
	return enabled[motor];
}


RobotMotors::RobotMotors(int enPorts[4],int pwmPorts[4],int m1Ports[4],int m2Ports[4],bool inverted[4]){
	
	int enPortsF1[2]={enPorts[0],enPorts[1]};
	int pwmPortsF1[2]={pwmPorts[0],pwmPorts[1]};
	int m1PortsF1[2];
	int m2PortsF1[2];
	
	if(inverted[0]){
		m1PortsF1[1]=m1Ports[0];
		m1PortsF1[0]=m1Ports[1];
	}
	else{
		m1PortsF1[0]=m1Ports[0];
		m1PortsF1[1]=m1Ports[1];
	}
	if(inverted[1]){
		m2PortsF1[1]=m2Ports[0];
		m2PortsF1[0]=m2Ports[1];
	}
	else{
		m2PortsF1[0]=m2Ports[0];
		m2PortsF1[1]=m2Ports[1];
	}
	motorsAB=new VNH5019(enPortsF1,pwmPortsF1,m1PortsF1,m2PortsF1);


	int enPortsF2[2]={enPorts[2],enPorts[3]};
	int pwmPortsF2[2]={pwmPorts[2],pwmPorts[3]};
	int m1PortsF2[2];
	int m2PortsF2[2];

	if(inverted[2]){
		m1PortsF2[1]=m1Ports[2];
		m1PortsF2[0]=m1Ports[3];
	}
	else{
		m1PortsF2[0]=m1Ports[2];
		m1PortsF2[1]=m1Ports[3];
	}
	if(inverted[3]){
		m2PortsF2[1]=m2Ports[2];
		m2PortsF2[0]=m2Ports[3];
	}
	else{
		m2PortsF2[0]=m2Ports[2];
		m2PortsF2[1]=m2Ports[3];
	}
	motorsCD=new VNH5019(enPorts,pwmPortsF2,m1PortsF2,m2PortsF2);
	motorsAB->enableShield();
	motorsCD->enableShield();
}
void RobotMotors::setMotors(int motors,int pw){
	int cPw=pw;
	int dir=0;
	if(pw>0)
		dir=VNH_FWD;
	if(pw<0)
		dir=VNH_REV;

	if(cPw>=ROBOT_MOTOR_D){
		motorsCD->setMotor(VNH_MOTOR_2,absolute(pw),dir);
		cPw-=ROBOT_MOTOR_D;
	}
	if(cPw>=ROBOT_MOTOR_C){
		motorsCD->setMotor(VNH_MOTOR_1,absolute(pw),dir);
		cPw-=ROBOT_MOTOR_C;
	}
	if(cPw>=ROBOT_MOTOR_B){
		motorsAB->setMotor(VNH_MOTOR_2,absolute(pw),dir);
		cPw-=ROBOT_MOTOR_B;
	}
	if(cPw>=ROBOT_MOTOR_A){
		motorsAB->setMotor(VNH_MOTOR_1,absolute(pw),dir);
		cPw-=ROBOT_MOTOR_A;
	}
}
RobotControl::RobotControl(RobotMotors* motors,int pwScale){
	robotMotors=motors;
	scale=pwScale;
	if(scale<0)
		scale*=-1;
}
void RobotControl::vectorMove(float angle,int maxSpeed){
	double eulerToRadians=angle*PI/180.0+45.0;
	if(eulerToRadians>PI*2){
		eulerToRadians-=PI*2;
	}
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_D,(int)(sin(eulerToRadians)*((float)maxSpeed/(float)scale)*255));
	robotMotors->setMotors(ROBOT_MOTOR_B+ROBOT_MOTOR_C,(int)(cos(eulerToRadians)*((float)maxSpeed/(float)scale)*255));
}
void RobotControl::moveFwd(int speed){
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_B+ROBOT_MOTOR_C+ROBOT_MOTOR_D,(int)((float)speed/(float)scale*255));
}
void RobotControl::moveRev(int speed){
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_B+ROBOT_MOTOR_C+ROBOT_MOTOR_D,(int)((float)-speed/(float)scale*255));
}
void RobotControl::moveLeft(int speed){
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_D,(int)((float)-speed/(float)scale*255));
	robotMotors->setMotors(ROBOT_MOTOR_B+ROBOT_MOTOR_C,(int)((float)speed/(float)scale*255));
}
void RobotControl::moveRight(int speed){
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_D,(int)((float)speed/(float)scale*255));
	robotMotors->setMotors(ROBOT_MOTOR_B+ROBOT_MOTOR_C,(int)((float)-speed/(float)scale*255));
}
void RobotControl::turnLeft(int speed){
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_B,(int)((float)-speed/(float)scale*255));
	robotMotors->setMotors(ROBOT_MOTOR_C+ROBOT_MOTOR_D,(int)((float)speed/(float)scale*255));
}
void RobotControl::turnRight(int speed){
	robotMotors->setMotors(ROBOT_MOTOR_A+ROBOT_MOTOR_B,(int)((float)speed/(float)scale*255));
	robotMotors->setMotors(ROBOT_MOTOR_C+ROBOT_MOTOR_D,(int)((float)-speed/(float)scale*255));
}