#define BEGIN 6
bool n[8]= {0};
void setup() {
  for(int i=BEGIN; i<=BEGIN+7; i++)
    pinMode(i,OUTPUT);
}

void loop() {
  for(int i=0; i<8; i++)
    digitalWrite(i+BEGIN, n[i]);
}
