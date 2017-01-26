bool led = true;
void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  led = digitalRead(5);
  Serial.println(led);
  digitalWrite(4,led);
  digitalWrite(2,led);
}
