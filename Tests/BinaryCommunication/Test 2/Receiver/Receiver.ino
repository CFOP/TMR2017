#define BEGIN 41
char p=0;
char boolChar(){
  char c=0;
  for(int i=0; i<8; i++){
    if(digitalRead(i+BEGIN)){
        c+=1<<(7-i);
    }
  }
  return c;
}
void setup() {
  Serial.begin(9600);
  for(int i=BEGIN-1; i<=BEGIN+7; i++)
    pinMode(i,INPUT_PULLUP);
  pinMode(36,INPUT);
}

void loop(){
  char a;
 // while(!digitalRead(40));
  a=~boolChar();
  if(p!=a)
    Serial.println(a);
  p=a;
  //while(!digitalRead(36));
  //while(digitalRead(36));
}
