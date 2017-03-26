/*
Developed by:
 _______  __    __  _____    _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|  |   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|   |  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__   |  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|  |_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 

Updated on 18/02/2017
*/
#include <Wire.h>
#include <HMC5883L.h>
HMC5883L compass=HMC5883L(HMC5883L_DEFAULT_ADDRESS);
void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Initialize the sensor's i2c bus
  compass.init();
  // Set sesnor frontal angle to current offset angle to Magnetic North
  compass.setStartingAngle();
}

void loop() {
  // Print sensor heading
  Serial.println(compass.getAngle());
}