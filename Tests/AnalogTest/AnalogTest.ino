void setup() {
  Serial.begin(9600);

}

void loop() {
  for(int i=A0; i<=A5; i++){
    Serial.print(analogRead(i));
    Serial.print('\t');
  }
  Serial.print('\n');
}
