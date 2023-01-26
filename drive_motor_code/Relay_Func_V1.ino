int IN1 = 5;
int IN2 = 6;

/*
One second is 1000 ms
10 = Hi Lo
1 = Lo Hi
0 = Lo Lo
*/

/*
const long oneSec = 1000;
const long tenSecs = onSec * 10;
const long oneMin = oneSec * 60;
*/
void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

int forward(int x){
  int z = 10; 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(x);
  return z;
}
int backward(int x){
  int z = 01;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(x);
  return z;
}
int stop(){
  int z = 0;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  return z;
}

void loop(){
  /*digitalWrite(IN1, HIGH);//Forward
  digitalWrite(IN2, LOW);
  delay(2000);

  digitalWrite(IN1, LOW);//Backward
  digitalWrite(IN2, HIGH);
  delay(2000);

  digitalWrite(IN1, LOW);//Stop
  digitalWrite(IN2, LOW);
  delay(2000);*/
}

