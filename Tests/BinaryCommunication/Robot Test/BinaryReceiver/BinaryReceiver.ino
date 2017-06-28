#define BEGIN 52
unsigned int boolChar() {
  unsigned int c = 0;
  for (int i = 0; i < 7; i++) {
    if (digitalRead(BEGIN-i)) {
      c += 1 << (i);
      Serial.print(0);
    }
    else{
      Serial.print(1);
    }
  }
  Serial.print(!digitalRead(BEGIN-8));
  Serial.print(" ");
  Serial.print(c);
  Serial.println();
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
