#include <HMC5883L.h>
#include <RobotControl.h>
#define POWER 20.0
#define MA 1
#define MB 2
#define MC 4
#define MD 8
#define EN1 22
#define EN2 23
#define EN3 28
#define EN4 29


#define ASP 3
#define BSP 2
#define CSP 4
#define DSP 5


#define AM1 30
#define AM2 32

#define BM1 24
#define BM2 26

#define CM1 25
#define CM2 27

#define DM1 31
#define DM2 33

VNHMotor motorA=VNHMotor(ASP,AM1,AM2,EN1,255,false);
VNHMotor motorB=VNHMotor(BSP,BM1,BM2,EN2,255,false);
VNHMotor motorC=VNHMotor(CSP,CM1,CM2,EN3,255,false);
VNHMotor motorD=VNHMotor(DSP,DM1,DM2,EN4,255,false);

void setup() {
  motorA.setupMotor();
  motorB.setupMotor();
  motorC.setupMotor();
  motorD.setupMotor();
}

void loop() {
  // put your main code here, to run repeatedly:
  motorA.set(POWER);
  motorB.set(POWER);
  motorC.set(POWER);
  motorD.set(POWER);
  delay(1000);
  motorA.set(0.0);
  motorB.set(0.0);
  motorC.set(0.0);
  motorD.set(0.0);
  delay(1000);
  motorA.set(-POWER);
  motorB.set(-POWER);
  motorC.set(-POWER);
  motorD.set(-POWER);
  delay(1000);
  motorA.set(0.0);
  motorB.set(0.0);
  motorC.set(0.0);
  motorD.set(0.0);
  delay(1000);
}
