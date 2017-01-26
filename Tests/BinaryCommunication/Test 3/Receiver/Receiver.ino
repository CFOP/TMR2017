void setup() {
  Serial.begin(9600);
  pinMode(50, INPUT_PULLUP);
  pinMode(52, OUTPUT);
  pinMode(51, INPUT_PULLUP);
  pinMode(53, OUTPUT);
}

void loop() {
  digitalWrite(52,digitalRead(50));
  digitalWrite(53,digitalRead(51));
}
