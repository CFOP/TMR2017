/*
Developed by:
 _______  __    __  _____    _____  __    __     _____     _____    _____  _______   ______ 
|__   __||  |__|  ||   __|  |   __||  |__|  |   /  _  \   |   - |  |  _  ||__   __| |   ___|
   | |   |   __   ||   _|   |  |   |   __   |  /  /_\  \  |  |_||_ | | | |   | |   |__ |___ 
   | |   |  |  |  ||  |__   |  |__ |  |  |  | /   ___   \ |   __  || |_| |   | |    __|    |
   |_|   |__|  |__||_____|  |_____||__|  |__||___|   |___||__|__|_||_____|   |_|   |______| 

Updated on 25/02/2017
*/
#include <LightSensorBar.h>
LightSensorBar bar=LightSensorBar(A0);
void setup() {
  bar.calibrate();
}

void loop() {
  char c=bar.getLineDirection();
  Serial.println(c);
}