#include <Wire.h>
#include <HTInfraredSeeker.h>
HTInfraredSeeker seeker;
InfraredInput input;
void setup() {
  Serial.begin(9600);
  seeker.init();
}

void loop() {
  input=seeker.readSensorValues();
  Serial.println((String)input.direction+"\t"+(String)input.strength1+"\t"+(String)input.strength2+"\t"+(String)input.strength3+"\t"+(String)input.strength4+"\t"+(String)input.strength5+"\t"+(String)input.strengthAll);
}
