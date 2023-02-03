/*
Below is the relay control functions and button panel for 
controling the: Drill direction, Drill speed, and Tube direction.

*/

//Relay control Inputs
int IN1 = 2;
int IN2 = 3;  
int IN3 = 4;
int IN4 = 5;
int IN1speed = 6; //Drill speed control input for relay

//Button pins
int butt1 = 19;
int butt2 = 18;
int butt3 = 17;
int butt4 = 16;
int butt5 = 15;
int butt6 = 14;
int butt7 = 13;
int butt8 = 12;

//Latching Switch Cases, for button panel to work (Prob TEMP)
int tubeState = 2; 
int drillState = 2;
int drillSpeedState = 0;

/*
One second is 1000 ms
10 = Hi Lo Forward
1 = Lo Hi Backward
0 = Lo Lo Stop
*/


void setup(){
  //Setting up control pins for relays and buttons
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN1speed, OUTPUT);

  //Buttons
  pinMode(butt1, INPUT);
  pinMode(butt2, INPUT);
  pinMode(butt3, INPUT);
  pinMode(butt4, INPUT);
  pinMode(butt5, INPUT);
  pinMode(butt6, INPUT);
  pinMode(butt7, INPUT);
  pinMode(butt8, INPUT);

  //Set initial relay condition to LOW (Off)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  //For debugging (See output)
  Serial.begin( 9600 );
}


/*
Relay functions

=== LOW MUST COME BEFORE HIGH ALWAYS ===
*/

/*
Tube directionality function

1. Tube forward
2. Tube backward
3. Tube stop
*/
int tubeForward(){
  int z = 10; 
  digitalWrite(IN2, LOW);  //Low must always come before high
  digitalWrite(IN1, HIGH);
  return z;
}
int tubeBackward(){
  int z = 01;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  return z;
}
int tubeStop(){
  int z = 0;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  return z;
}

/*
Drill directionality function
This relay board has inverted inputs

1. Drill forward
2. Drill backward
3. Drill stop
*/
int drillForward(){
  digitalWrite(IN4, HIGH);    
  digitalWrite(IN3, LOW);
}
int drillBackward(){
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
int drillStop(){
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

/*
Switch case function for tube state

Default is off
*/
int tubeControl(){
  switch(tubeState){
    case 0:
      tubeForward();
      break;
    case 1:
      tubeBackward();
      break;
    case 2:
      tubeStop();
      break;
    default:
      tubeStop();
  }
}

/*
Switch case function for drill state

Default is off
*/
int drillControl(){
  switch(drillState){
    case 0:
      drillForward();
      break;
    case 1:
      drillBackward();
      break;
    case 2:
      drillStop();
      break;
    default:
      drillStop();
  }
}

/*
Reading tube button press

1. Forward
2. Backward
3. Stop
*/
int tubeRead(){
  if (digitalRead(butt1) == LOW){
    tubeState = 0;
  }
  if (digitalRead(butt2) == LOW){
    tubeState = 1;
  }
  if (digitalRead(butt3) == LOW){
    tubeState = 2;
  }
}

/*
Reading drill button press

1. Forward
2. Backward
3. Stop
*/
int drillRead(){
  if (digitalRead(butt4) == LOW){
    drillState = 0;
  }
  if (digitalRead(butt5) == LOW){
    drillState = 1;
  }
  if (digitalRead(butt6) == LOW){
    drillState = 2;
  }
}

/*
Reading speed button press

1. Slow (LOWw)
2. Fast (HIGH)
*/
int speedRead(){
  if (digitalRead(butt7) == LOW){
    digitalWrite(IN1speed, LOW);
  }
  if (digitalRead(butt8) == LOW){
    digitalWrite(IN1speed, HIGH);
  }
}

void loop(){
  tubeControl();
  drillControl();
  tubeRead();
  drillRead();
  speedRead();

  
  Serial.println(tubeState);
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
