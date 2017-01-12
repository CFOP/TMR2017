void setup() {
  Serial.begin(9600);
  pinMode(52, OUTPUT);
  pinMode(50, OUTPUT);
}

void loop() {
  Serial.println(digitalRead(50));
  if(digitalRead(50))
    digitalWrite(52, 0);
   else digitalWrite(52, 1);
}
