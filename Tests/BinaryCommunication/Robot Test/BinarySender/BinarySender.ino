#define BEGIN 2
bool n[9];
int absolute(int n){
  if(n<0)
    return -n;
  return n;
}

void setNull(){
  for(int i=0; i<8;i++){
    digitalWrite(i+BEGIN, LOW);
  }
}

void charBoolNegs(int m){
  int c=absolute(m);
  for(int i=0;i<8;i++){
    if(c%2==0){
      n[i]=true;
      Serial.print(0);
    }
    else{
      n[i]=false;
      Serial.print(1);
    }
    c/=2;
  }
  n[8]=false;
  if(m<0)
    n[8]=true;
  Serial.print(n[8]);  
  Serial.println();
  
}

void charBool(int m){
  int c=m;
  for(int i=0;i<9;i++){
    if(c%2==0){
      n[i]=true;
      Serial.print(0);
    }
    else{
      n[i]=false;
      Serial.print(1);
    }
    c/=2;
  }
  Serial.println();
  for(int i2=0; i2<9;i2++){
    digitalWrite(i2+BEGIN, n[i2]);
  }
}
void setup() {
  Serial.begin(9600);
  
  for(int i=0; i<9; i++)
    pinMode(i+BEGIN,OUTPUT);
}

void loop() {
  for(int i=0,r=1;i<9;i++){
    charBool(r);
    r*=2;
    delay(1000);
  }
}
