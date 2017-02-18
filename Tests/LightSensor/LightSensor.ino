#define MARGIN 20
int A[8];
bool r,l,m;
void setup() {
  Serial.begin(9600);
  delay(500);
  for(int i=0; i<=7; i++){
    A[i]=analogRead(i+A0);
    /*Serial.print(A[i]);
    Serial.print('\t');*/
  }
}
void loop() {
  r=false;
  l=false;
  m=false;
  for(int i=0; i<=2; i++){  
      r+=(A[i]+MARGIN<analogRead(A0+i));
  }
  for(int i=0; i<=1; i++){
    if(A[i+3]+MARGIN<analogRead(A3+i))  
      m=true;
  }
  for(int i=0; i<=2; i++){
    if(A[i+5]+MARGIN<analogRead(A5+i))  
      l=true;
  }
  
  for(int i=A0; i<=A7; i++){
    Serial.print(A[i-A0]);
    Serial.print("-");
    Serial.print(analogRead(i));
    Serial.print('\t');  
  }
  
  if(m || (r&&l)){
    Serial.println("m");
  }
  else if(r){
    Serial.println("r");
  }
  else if(l){
    Serial.println("l");
  }
  else{
    Serial.println("o");  
  }
  
}
