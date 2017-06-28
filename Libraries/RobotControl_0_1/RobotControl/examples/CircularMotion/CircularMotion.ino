/*
Developed by:
 _______  __    __  _____    _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|  |   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|   |  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__   |  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|  |_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 

Updated on 06/08/2017
*/
#include <Wire.h>
#include <HMC5883L.h>
#include <RobotControl.h>

#define MAX_PW 255
#define POWER 30.0
#define MOVEMENT_ANGLE_CHANGE 5.0
#define ANGLE_CHG_RATE_MS 20

// Enable motor ports
#define EN_MA 22
#define EN_MB 23
#define EN_MC 28
#define EN_MD 29
// PWM motor ports
#define A_PWM 3
#define B_PWM 2
#define C_PWM 4
#define D_PWM 5
// Motor input ports
#define AM1_IN 30
#define AM2_IN 32
#define BM1_IN 24
#define BM2_IN 26
#define CM1_IN 25
#define CM2_IN 27
#define DM1_IN 31
#define DM2_IN 33
// Instantiating the magnetometer
HMC5883L magSensor = HMC5883L(HMC5883L_DEFAULT_ADDRESS);
// Instantiating the motors
VNHMotor motorA = VNHMotor(A_PWM, AM1_IN, AM2_IN, EN_MA, MAX_PW, false);
VNHMotor motorB = VNHMotor(B_PWM, BM1_IN, BM2_IN, EN_MB, MAX_PW,false);
VNHMotor motorC = VNHMotor(C_PWM, CM1_IN, CM2_IN, EN_MC, MAX_PW,false);
VNHMotor motorD = VNHMotor(D_PWM, DM1_IN, DM2_IN, EN_MD, MAX_PW,false);
// Instantiating the RobotControl object
RobotControl controller(&motorA, &motorB, &motorC, &motorD, &magSensor);
void setup() {
  Serial.begin(9600);
  // Initialize motor ports as outputs
  motorA.setupMotor();
  motorB.setupMotor();
  motorC.setupMotor();
  motorD.setupMotor();
  
  Wire.begin();
  // Initialize the magnetometer's i2c bus
  magSensor.init();
  // Set sesnor frontal angle to current offset angle to Magnetic North
  magSensor.setStartingAngle();
}

void loop() {
  // Circular motion loop
  for(double i = 0.0;i <= 360.0; i += MOVEMENT_ANGLE_CHANGE){
    // Vector move in all directions divisible by MOVEMENT_ANGLE_CHANGE
    controller.vectorMove(i, POWER, ANGLE_CHG_RATE_MS);
  }
}
