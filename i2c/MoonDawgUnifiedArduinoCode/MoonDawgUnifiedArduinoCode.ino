#include <Wire.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

#define SLAVE_ADDRESS 0x08

#define address1 0x80
#define address2 0x81

//Relay pins for auger and drill
//Tube relays
int IN1 = 2;
int IN2 = 3; 
//Drill relays
int IN3 = 4;
int IN4 = 5;
//Relay pins for linear actuators
//Chasis actuator
int IN5 = 6;
int IN6 = 7;
//Auger actuator
int IN7 = 8;
int IN8 = 9;

//Limit Switch pins
int limitSwitchRear = 12;
int limitSwitchForward = 13;
//Limit Switch Latching Variables
bool pressedRear = false;
bool pressedForward = false;

//Latching Switch Cases, for non-continuous commands
int tubeState = 2; 
int drillState = 2;
int chasisActuatorState = 2;
int augerActuatorState = 2;

//Relay control byte???
byte byte_to_use[3];

// Type bytes
#define MOVEMENT = 0x00
#define AUGER = 0x10
#define TILT = 0x20
#define AUTO = 0x30

// Command bytes
#define FORWARD = 0x01
#define BACKWARD = 0x02
#define LEFT = 0x03
#define RIGHT = 0x04
#define STOP = 0x05
#define CLOCKWISE = 0x11
#define COUNTERCLOCKWISE = 0x12
#define STOP_SPIN = 0x13
#define STOP_MOVE = 0x14
#define BODY_FORWARD = 0x21
#define BODY_BACKWARD = 0x22
#define AUGER_FORWARD = 0x23
#define AUGER_BACKWARD = 0x24
#define BODY_STOP = 0x25
#define AUGER_STOP = 0x26
#define ENABLE_DRIVE = 0x31
#define DISABLE_DRIVE = 0x32
#define ENABLE_DIG = 0x33
#define DISABLE_DIG = 0x34

SoftwareSerial serial(10,11);
RoboClaw roboclaw(&serial,10000);

bool command_finish = true;

void startMotor(int direction, int speed) {
  
  // Determine which direction we will move
  // Then, start the motors in that direction
  switch(direction) {
    case FORWARD:
      roboclaw.BackwardM1(address1, speed);
      roboclaw.BackwardM2(address1, speed);
      roboclaw.BackwardM1(address2, speed);
      roboclaw.BackwardM2(address2, speed);
      break;
    case BACKWARD:
      roboclaw.ForwardM1(address1, speed);
      roboclaw.ForwardM2(address1, speed);
      roboclaw.ForwardM1(address2, speed);
      roboclaw.ForwardM2(address2, speed);
      break;
    case LEFT:
      roboclaw.ForwardM1(address1, speed);
      roboclaw.ForwardM2(address1, speed);
      roboclaw.BackwardM1(address2, speed);
      roboclaw.BackwardM2(address2, speed);
      break;
    case RIGHT:
      roboclaw.ForwardM1(address2, speed);
      roboclaw.ForwardM2(address2, speed);
      roboclaw.BackwardM1(address1, speed);
      roboclaw.BackwardM2(address1, speed);
      break;
    case STOP:
      roboclaw.ForwardM1(address2, 0);
      roboclaw.ForwardM2(address2, 0);
      roboclaw.BackwardM1(address1, 0);
      roboclaw.BackwardM2(address1, 0);
      break;
    default:
      break;
  }      
}

void startAuger(int command) {

  // Determine which command was sent
  // Then, call that function
  switch(command) {
    case CLOCKWISE:
      break;
    case COUNTERCLOCKWISE:
      break;
    case FORWARD:
      break;
    case BACKWARD:
      break;
    case STOP_SPIN:
      break;
    case STOP_MOVE:
      break;
    default:
      break;
  }

}

void startTilt(int command) {

  // Determine which command was sent
  // Then, call that function
  switch(command) {
    case BODY_FORWARD:
      break;
    case BODY_BACKWARD:
      break;
    case AUGER_FORWARD:
      break;
    case AUGER_BACKWARD:
      break;
    case BODY_STOP:
      break;
    case AUGER_STOP:
      break;
    default:
      break;
  }

}

void receiveData(int byteCount)
{


  // Create an array and store all information from the incoming data in it.
  // This will let use all of the bytes
  //
  // Item 0 will be the type of command to be issued (movement, auger, tilt, auto)
  // Item 1 will be the actual command to be issued (forward, backward, etc.)
  // Item 2 will be the speed for movement commands
  int incomingData[byteCount];
  for (int i = 0; i < byteCount; i++) {
    incomingData[i] = Wire.read();
  }

  // Determine what type of operation we are doing
  // Then, call that function (e.g. startMotor for movement)
  switch(incomingData[0]) {
    case MOVEMENT:
      startMotor(incomingData[1], incomingData[2]);
      break;
    case AUGER:
      startAuger(incomingData[1]);
      break;
    case TILT:
      startTilt(incomingData[1]);
      break;
    case AUTO: // not used at the moment
      break;
    default:
      break;
  }

}

/* **************************************************************
**           Beginning of Relay control functions              **
************************************************************** */

/*
Relay functions

=== LOW MUST COME BEFORE HIGH ALWAYS ===
*/

/*
Chasis linear actuator directionality function

1. Actuator forward
2. Actuator backward
3. Actuator stop
*/

void chasisActuatorForward(){
  Serial.println("chasis actuator forward"); 
  digitalWrite(IN7, LOW);  //Low must always come before high
  digitalWrite(IN6, HIGH);
}
void chasisActuatorBackward(){
  Serial.println("chasis actuator backward");
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, HIGH);
}
void chasisActuatorStop(){
  Serial.println("chasis actuator stop");
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);
}

/*
Auger linear actuator directionality function

1. Actuator forward
2. Actuator backward
3. Actuator stop
*/

void augerActuatorForward(){
  Serial.println("auger actuator forward"); 
  digitalWrite(IN9, LOW);  //Low must always come before high
  digitalWrite(IN8, HIGH);
}
void augerActuatorBackward(){
  Serial.println("auger actuator backward");
  digitalWrite(IN8, LOW);
  digitalWrite(IN9, HIGH);
}
void augerActuatorStop(){
  Serial.println("auger actuator stop");
  digitalWrite(IN8, LOW);
  digitalWrite(IN9, LOW);
}

/*
Tube directionality function

1. Tube forward
2. Tube backward
3. Tube stop
*/
void tubeForward(){
  Serial.println("tube forward"); 
  digitalWrite(IN2, LOW);  //Low must always come before high
  digitalWrite(IN1, HIGH);
}
void tubeBackward(){
  Serial.println("tube backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void tubeStop(){
  Serial.println("tube stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

/*
Drill directionality function
This relay board has inverted inputs

1. Drill forward
2. Drill backward
3. Drill stop
*/
void drillForward(){
  Serial.println("drill foward");
  digitalWrite(IN4, HIGH);    
  digitalWrite(IN3, LOW);
  Serial.println("INSIDE DRILL FORWARD");
}
void drillBackward(){
  Serial.println("drill foward");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void drillStop(){
  Serial.println("drill stop");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

/*
Switch case function for chasis linear actuator state

Default is off
*/

void chasisActuatorControl(){
  Serial.println("INSIDE CHASISACTUATORCONTROL");
  switch(chasisActuatorState){
    case '0':
      chasisActuatorForward();
      break;
    case '1':
      chasisActuatorBackward();
      break;
    case '2':
      chasisActuatorStop();
      break;
    default:
      chasisActuatorStop();
  }
}

/*
Switch case function for auger linear actuator state

Default is off
*/

void chasisActuatorControl(){
  Serial.println("INSIDE AUGERACTUATORCONTROL");
  switch(augerActuatorState){
    case '0':
      augerActuatorForward();
      break;
    case '1':
      augerActuatorBackward();
      break;
    case '2':
      augerActuatorStop();
      break;
    default:
      augerActuatorStop();
  }
}

/*
Switch case function for tube state

Default is off
*/
void tubeControl(){
  Serial.println("INSIDE TUBECONTROL");
  switch(tubeState){
    case '0':
      tubeForward();
      break;
    case '1':
      tubeBackward();
      break;
    case '2':
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
void drillControl(){
  Serial.println("INSIDE DRILL CONTROL");
  switch(drillState){
    case '0':
      drillForward();
      Serial.println("DRILL FORWARD");
      break;
    case '1':
      drillBackward();
      break;
    case '2':
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
void tubeRead(){
  if(byte_to_use[1] == '4'){
    tubeState = 0;
  }
  if(byte_to_use[1] == '5'){
    tubeState = 1;
  }
  if(byte_to_use[1] == '6'){
    tubeState = 2;
  }  
  Serial.print("tubeState: ");
  Serial.println(tubeState);
  // if (digitalRead(butt1) == LOW){
  //   tubeState = 0;
  // }
  // if (digitalRead(butt2) == LOW){
  //   tubeState = 1;
  // }
  // if (digitalRead(butt3) == LOW){
  //   tubeState = 2;
  // }
}

/*
Reading drill button press

1. Forward
2. Backward
3. Stop
*/
void drillRead(){
  if(byte_to_use[1] == '4'){
    drillState = 0;
  }
  if(byte_to_use[1] == '5'){
    drillState = 1;
  }
  if(byte_to_use[1] == '6'){
    drillState = 2;
  }
  Serial.print("drillState: ");
  Serial.println(drillState);
  // if (digitalRead(butt4) == LOW){
  //   drillState = 0;
  // }
  // if (digitalRead(butt5) == LOW){
  //   drillState = 1;
  // }
  // if (digitalRead(butt6) == LOW){
  //   drillState = 2;
  // }
}

/*
Limit Switch

1. Rear == High - Auger stops and motion stops
2. Forward == High - Motion stops and auger continues

Eventually a time command will be placed as to have the auger automatically move
after a set amount of time.
*/

void limitSwitches(){
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

void loop() {
  //call limit switch function to check if limit is reached      
  limitSwitches();

  //Something related to I2C that does something
  if(command_finished){
    if(byte_to_use[0] == 'g'){     
    } else if(byte_to_use[0] == 'C'){
      tubeRead();
      tubeControl();
      Serial.println("Running TUBE CONTROL");
    } else if(byte_to_use[0] == 'd'){
      Serial.println("Running Drill Read");
      Serial.println("Running Drill Control");
      drillRead();
      drillControl();
    }  
}

void setup() 
{
  roboclaw.begin(38400);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  //Setting up control pins for relays, buttons, and limit switches
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //Limit Switches
  //Rear = Auger stop motion stop at the back of the mechanism
  //Forward = Motion stop at the front of the mechanism
  pinMode(limitSwitchRear, INPUT);
  pinMode(limitSwitchForward, INPUT);
  //Set initial relay condition to LOW (Off) for relays
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
