#define BEGIN 41
void setup() {
  Serial.begin(9600);
  for(int i=BEGIN-1; i<=BEGIN+7; i++)
    pinMode(i,INPUT_PULLUP);
}

void loop() {
  for(int i=BEGIN-1; i<=BEGIN+7; i++)
    Serial.print(digitalRead(i));
  Serial.print('\n');
}
