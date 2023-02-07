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

//Limit Switch pins
int limitSwitchRear = 11;
int limitSwitchForward = 10;
//Limit Switch Latching Variables
bool pressedRear = false;
bool pressedForward = false;

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
  //Setting up control pins for relays, buttons, and limit switches
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

  /*
  Limiit Switches
  Rear = Auger stop motion stop at the back of the mechanism
  Forward = Motion stop at the front of the mechanism
  */
  pinMode(limitSwitchRear, INPUT);
  pinMode(limitSwitchForward, INPUT);


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

/*
Limit Switch

1. Rear == High - Auger stops and motion stops
2. Forward == High - Motion stops and auger continues

Eventually a time command will be placed as to have the auger automatically move
after a set amount of time.
*/

int limitSwitches(){
  if(pressedRear == false){
    if(digitalRead(limitSwitchRear) == LOW){
        tubeState = 3;
        drillState = 3;
        pressedRear = true;
    }
  }
  if(digitalRead(limitSwitchRear) == HIGH){
    pressedRear = false;
  }
  if(pressedForward == false){
    if(digitalRead(limitSwitchForward) == LOW){
      tubeState = 3;
      pressedForward = true;
    }
  }
  if(digitalRead(limitSwitchForward) == HIGH){
    pressedForward = false;
  }
}

void loop(){
  limitSwitches();
  tubeControl();
  drillControl();
  tubeRead();
  drillRead();
  speedRead();


  if (digitalRead(limitSwitchForward) == HIGH){
    Serial.print("High");
  }
  if (digitalRead(limitSwitchForward) == LOW){
    Serial.print("Low");
  }
  Serial.println(pressedForward);
}
