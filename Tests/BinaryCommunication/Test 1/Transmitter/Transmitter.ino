#define BEGIN 2
bool n[8]= {1,1,1,1,1,1,1,1};
void setup() {
  for(int i=BEGIN; i<=BEGIN+7; i++)
    pinMode(i,OUTPUT);
}

void loop() {
  for(int i=0; i<8; i++)
    digitalWrite(i+BEGIN, n[i]);
}
