#define BEGIN 52
unsigned int boolChar() {
  unsigned int c = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(BEGIN-i)) {
      c += 1 << (i);
      Serial.print(0);
    }
    else{
      Serial.print(1);
    }
  }
  Serial.print(!digitalRead(BEGIN-8));
  Serial.println();
  if(digitalRead(BEGIN-8))
    return -c;
  return c;
}
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 9; i++)
    pinMode(BEGIN-i, INPUT);
}
void loop() {
  boolChar();
}
