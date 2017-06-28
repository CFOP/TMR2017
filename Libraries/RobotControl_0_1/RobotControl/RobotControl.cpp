/*
Developed by:
 _______  __    __  _____	 	 _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|		|   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|		|  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__		|  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|		|_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 
--------------------------
RobotControl.cpp
Updated on 28/05/2017
--------------------------
*/
#include "RobotControl.h"
#include "Arduino.h"
#include "Wire.h"
#include "HMC5883L.h"

VNHMotor::VNHMotor(int powerPort,int motorPort1,int motorPort2,int enablePort,int maxPower,bool inverted){
	inv=inverted;
	pwPort=powerPort;
	port1=motorPort1;
	port2=motorPort2;
	enPort=enablePort;
	maxPw=maxPower;
	
	if(maxPw>255){
		maxPw=255;
	}
}
void VNHMotor::setupMotor(){
	pinMode(pwPort,OUTPUT);
	pinMode(port1,OUTPUT);
	pinMode(port2,OUTPUT);
	pinMode(enPort,OUTPUT);
}
void VNHMotor::set(double power){
	int pw=(int)(maxPw*power/100.0);
	if(pw==0){
		digitalWrite(pwPort,LOW);
		digitalWrite(port1,LOW);
		digitalWrite(port2,LOW);
		digitalWrite(enPort,LOW);
	}
	else if(pw<0){
		if(!inv){
			analogWrite(pwPort,-pw);
			digitalWrite(port1,HIGH);
			digitalWrite(port2,LOW);
			digitalWrite(enPort,HIGH);
		}
		else{
			analogWrite(pwPort,-pw);
			digitalWrite(port1,LOW);
			digitalWrite(port2,HIGH);
			digitalWrite(enPort,HIGH);
		}
	}
	else{
		if(!inv){
			analogWrite(pwPort,pw);
			digitalWrite(port1,LOW);
			digitalWrite(port2,HIGH);
			digitalWrite(enPort,HIGH);
		}
		else{
			analogWrite(pwPort,pw);
			digitalWrite(port1,HIGH);
			digitalWrite(port2,LOW);
			digitalWrite(enPort,HIGH);
		}
	}
}
void VNHMotor::stopMotor(){
	set(0.0);
}
double RobotControl::toAngle(double angle){
  double res=angle;
  if(res>360.0){
    res-=360.0;
  }
  if(res<0.0){
    res+=360.0;
  }
  return res;
}
double RobotControl::degreesToRadians(double degrees){
  return degrees*PI/180.0;
}
RobotControl::RobotControl(VNHMotor* motorA,VNHMotor* motorB,VNHMotor* motorC,VNHMotor* motorD,float* headingAddr){
	mode=0;
	motors=new VNHMotor*[4]{motorA,motorB,motorC,motorD};
	magnetometer=NULL;
}
RobotControl::RobotControl(VNHMotor* motorA,VNHMotor* motorB,VNHMotor* motorC,VNHMotor* motorD,HMC5883L* robotMagnetometer){
	mode=1;
	motors=new VNHMotor*[4]{motorA,motorB,motorC,motorD};
	magnetometer=robotMagnetometer;
}
void RobotControl::setMotors(unsigned int mts,double power){
	int ms=mts;
	if(ms>=MD){
		motors[3]->set(power);
		ms-=MD;
	}
	if(ms>=MC){
		motors[2]->set(power);
		ms-=MC;
	}
	if(ms>=MB){
		motors[1]->set(power);
		ms-=MB;
	}
	if(ms>=MA){
		motors[0]->set(power);
	}
}
void RobotControl::stopRobot(){
	setMotors(MA+MB+MC+MD,0.0);
}
void RobotControl::vectorMove(double movementAngle,double power){
	float angle=0.0f;
	if(mode==0){
		angle=*heading;
	}
	else{
		angle=magnetometer->getAngle();
	}
	int adSpeed=(int)(sin(degreesToRadians(toAngle((360.0-movementAngle)+45)))*power);
	int bcSpeed=(int)(cos(degreesToRadians(toAngle((360.0-movementAngle)+45)))*power);

	setMotors(MA,adSpeed); 
	if(movementAngle<=45.0||movementAngle>=315.0||(movementAngle>=135.0&&movementAngle<=225.0)){
		setMotors(MB,bcSpeed);
		if(angle>180){
		  setMotors(MC,(int)(bcSpeed+(360.0f-angle)/180.0f*78.43f));
		  setMotors(MD,(int)(adSpeed+(360.0f-angle)/180.0f*78.43f));
		}
		else{
		  setMotors(MC,(int)(bcSpeed-(angle/180.0f*78.43f)));
		  setMotors(MD,(int)(adSpeed-(angle/180.0f*78.43f)));
		}
	}
	else{
		setMotors(MC,bcSpeed);
		if(angle<180){
		  setMotors(MB,(int)(bcSpeed+(angle)/180.0f*78.43f));
		  setMotors(MD,(int)(adSpeed-(angle)/180.0f*78.43f));
		}
		else{
		  setMotors(MB,(int)(bcSpeed-(360.0f-angle)/180.0f*78.43f));
		  setMotors(MD,(int)(adSpeed+(360.0f-angle)/180.0f*78.43f));
		}
	}
}

void RobotControl::vectorMove(double movementAngle,double power,unsigned int ms){
	if(mode==1){
		unsigned long int timeMark=millis();
		while((millis()-timeMark)<=ms){
			vectorMove(movementAngle,power);
		}
	}
	else{
		stopRobot();
	}
}
void RobotControl::vectorMoveLocked(double movementAngle,double power,float lockedAngle){
	float angle=0.0f;
	if(mode==0){
		angle=*heading;
	}
	else{
		angle=toAngle(magnetometer->getAngle()-lockedAngle);
	}
	int adSpeed=(int)(sin(degreesToRadians(toAngle((360.0-movementAngle)+45)))*power);
	int bcSpeed=(int)(cos(degreesToRadians(toAngle((360.0-movementAngle)+45)))*power);
	setMotors(MA,adSpeed);
	if(movementAngle<=45.0||movementAngle>=315.0||(movementAngle>=135.0&&movementAngle<=225.0)){
		setMotors(MB,bcSpeed);
		if(angle>180){
		  setMotors(MC,(int)(bcSpeed+(360.0f-angle)/180.0f*78.43f));
		  setMotors(MD,(int)(adSpeed+(360.0f-angle)/180.0f*78.43f));
		}
		else{
		  setMotors(MC,(int)(bcSpeed-(angle/180.0f*78.43f)));
		  setMotors(MD,(int)(adSpeed-(angle/180.0f*78.43f)));
		}
	}
	else{
		setMotors(MC,bcSpeed);
		if(angle<180){
		  setMotors(MB,(int)(bcSpeed+(angle)/180.0f*78.43f));
		  setMotors(MD,(int)(adSpeed-(angle)/180.0f*78.43f));
		}
		else{
		  setMotors(MB,(int)(bcSpeed-(360.0f-angle)/180.0f*78.43f));
		  setMotors(MD,(int)(adSpeed+(360.0f-angle)/180.0f*78.43f));
		}
	}
	
}
void RobotControl::vectorMoveLocked(double movementAngle,double power,float lockedAngle,unsigned int ms){
	if(mode==1){
		unsigned long int timeMark=millis();
		while((millis()-timeMark)<=ms){
			vectorMoveLocked(movementAngle,power,lockedAngle);
		}
	}
	else{
		stopRobot();
	}
}
void RobotControl::moveFwd(double power){
	vectorMove(0.0,power);
}
void RobotControl::moveFwd(double power,unsigned int millis){
	vectorMove(0.0,power,millis);
}
void RobotControl::moveRev(double power){
	vectorMove(180.0,power);
}
void RobotControl::moveRev(double power,unsigned int millis){
	vectorMove(180.0,power,millis);
}
void RobotControl::moveRight(double power){
	vectorMove(90.0,power);
}
void RobotControl::moveRight(double power,unsigned int millis){
	vectorMove(90.0,power,millis);
}
void RobotControl::moveLeft(double power){
	vectorMove(270.0,power);
}
void RobotControl::moveLeft(double power,unsigned int millis){
	vectorMove(270.0,power,millis);
}
