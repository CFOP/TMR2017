#define BEGIN 3
#define CHAR 'b'
bool n[8];
void charBool(char c){
  for(int i=0; i<8; i++){
    if(c>=1<<(7-i)){
      n[i]=true;
      c-=1<<(7-i);
    }
    
    else n[i]=false;
  }
}
void setup() {
  for(int i=BEGIN-1; i<=BEGIN+7; i++)
    pinMode(i,OUTPUT);
}

void loop() {
  for(char j='a'; j<='z';j++){
    pinMode(2, HIGH);
    charBool(j);
    for(int i=0; i<8; i++){
      digitalWrite(i+BEGIN, n[i]);
    }
    pinMode(2, LOW);
    delay(200);
  }
}
