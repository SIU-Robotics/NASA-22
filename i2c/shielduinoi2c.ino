/*
SIUC MoonDawgs 2022-2023 Competition
Description: This code houses the motor controller functions for the driving mechanisms
of the robot.

*/

//------------------------initializations---------------
#include <SoftwareSerial.h>
#include <Wire.h>
#include "RoboClaw.h"

#define SLAVE_ADDRESS 0x08

#define address1 0x80
#define address2 0x81

//movement bytes
#define MOVEMENT 0x00
#define STOP 0x01
#define TFORWARD 0x02
#define TBACKWARD 0x03
#define TLEFT 0x04
#define TRIGHT 0x05
#define CFORWARD 0x06
#define CBACKWARD 0x07
#define CLEFT 0x08
#define CRIGHT 0x09

SoftwareSerial serial(10,11);
RoboClaw roboclaw(&serial,10000);

bool command_finish = true;

//------------------------------------------------------
//------------------------setup-------------------------
void setup() {
  roboclaw.begin(38400);

  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}
//------------------------------------------------------
//-----------------function calls-----------------------
void cforward();
void cbackward();
void cleft();
void cright();
void tforward();
void tbackward();
void tleft();
void tright();
void stop();
//------------------------------------------------------
//--------------------main loop-------------------------
void loop() {
  if(command_finished){
    if(data_to_echo == 'w') // Forward
    {
      Serial.println("Forward");
    } else if(data_to_echo == 's')
    {
      Serial.println("Backward");
    } else if(data_to_echo == 'a')
    {
      Serial.println("Left");
    } else if(data_to_echo =='d'){
      Serial.println("Right");
    }
    else if(data_to_echo == 'g')
    {
      Serial.println("Uni Stop");
    } else if(data_to_echo == 'i')
    {
      Serial.println("Timed F");
    } else if(data_to_echo =='k'){
      Serial.println("Timed Back");
    } else if(data_to_echo == 'j')
    {
      Serial.println("Timed Left");
    } else if(data_to_echo == 'l')
    {
      Serial.println("Timed Right");
    } else if(data_to_echo =='c')
    {
      Serial.println("Auger Foward");
    } else if(data_to_echo == 'v')
    {
      Serial.println("Auger Backward");
    } else if(data_to_echo == 'b')
    {
      Serial.println("Auger Stop");
    } else if(data_to_echo =='n')
    {
      Serial.println("Drill CC");
    } else if(data_to_echo == 'm')
    {
      Serial.println("Drill CCW");
    } else if(data_to_echo == 'h')
    {
      Serial.println("Drill Stop");
    } else if(data_to_echo =='t')
    {
      Serial.println("Lin Act Up");
    } else if(data_to_echo == 'y')
    {
      Serial.println("Lin Act Down");
    } else if(data_to_echo == 'u')
    {
      Serial.println("Lin Act Stop");
    } else {
      Serial.println("No Command");
    }
  }
}
//------------------------------------------------------
//--------------------function bodies-------------------
//--------------------i2c implementation----------------
void receiveData(int byteCount)
{
  Serial.print("BYTE COUNT: ");
  Serial.println(byteCount);
  int incomingData[byteCount];

  for (int i = 0; i < byteCount; i++) {
      incomingData[i] = Wire.read();
  }

  switch(incomingData[0]) {
    case MOVEMENT:
      // there will be a direction and a speed
      Serial.println("Type: Movement")
      if (incomingData[1] == TFORWARD) {
        Serial.println("Direction: 3 Seconds Forward");
      }
      else if (incomingData[1] == TBACKWARD) {
        Serial.println("Direction: 3 Seconds Backward");
      }
      else if (incomingData[1] == TLEFT) {
        Serial.println("Direction: 3 Seconds Left");
      }
      else if (incomingData[1] == TRIGHT) {
        Serial.println("Direction: 3 Seconds Right");
      }
      else {
        Serial.println("Direction: Unknown")
      }

      Serial.println("Speed: " + incomingData[2])      
  }
}

void sendData() {
  Wire.write(data_to_echo);  
}
//--------------------timed iterations------------------
void tforward()
{
//counter implements acceleration
    for(int i = 0; i <= 32; i++) {
    roboclaw.BackwardM1(address1, i);
    roboclaw.BackwardM2(address1, i);
    roboclaw.BackwardM1(address2, i);
    roboclaw.BackwardM2(address2, i);
    delay(50);    
  } //speed stays at 32 for 3 seconds
  delay(3000);
//counter implements deceleration
  for(int j = 32; j >= 0; j--) {
    roboclaw.BackwardM1(address1, j);
    roboclaw.BackwardM2(address1, j);
    roboclaw.BackwardM1(address2, j);
    roboclaw.BackwardM2(address2, j);
    delay(50);
  } 
}

void tbackward(){
  //test address 1 is right and address left is 2
  for(int i = 0; i <= 32; i++) {
    roboclaw.ForwardM1(address1, i);
    roboclaw.ForwardM2(address1, i);
    roboclaw.ForwardM1(address2, i);
    roboclaw.ForwardM2(address2, i);
    delay(50);    
  }
  delay(3000);
  for(int j = 32; j >= 0; j--) {
    roboclaw.ForwardM1(address1, j);
    roboclaw.ForwardM2(address1, j);
    roboclaw.ForwardM1(address2, j);
    roboclaw.ForwardM2(address2, j);
    delay(50);
  }
}

void tleft(){
  //test address 1 is right and address left is 2
  for(int i = 0; i <= 32; i++) {
    roboclaw.ForwardM1(address1, i);
    roboclaw.ForwardM2(address1, i);
    roboclaw.BackwardM1(address2, i);
    roboclaw.BackwardM2(address2, i);
    delay(50);    
  }
  delay(3000);
  for(int j = 32; j >= 0; j--) {
    roboclaw.ForwardM1(address1, j);
    roboclaw.ForwardM2(address1, j);
    roboclaw.BackwardM1(address2, j);
    roboclaw.BackwardM2(address2, j);
    delay(50);
  }
}

void tright(){
  //test address 1 is right and address left is 2
  for(int i = 0; i <= 32; i++) {
    roboclaw.ForwardM1(address2, i);
    roboclaw.ForwardM2(address2, i);
    roboclaw.BackwardM1(address1, i);
    roboclaw.BackwardM2(address1, i);
    delay(50);    
  }
  delay(3000);
  for(int j = 32; j >= 0; j--) {
    roboclaw.ForwardM1(address2, j);
    roboclaw.ForwardM2(address2, j);
    roboclaw.BackwardM1(address1, j);
    roboclaw.BackwardM2(address1, j);
    delay(50);
  }
}
//----------------constant iterations------------------
void cforward() {
//counter implements acceleration
  for(int i = 0; i <= 32; i++) {
    roboclaw.BackwardM1(address1, i);
    roboclaw.BackwardM2(address1, i);
    roboclaw.BackwardM1(address2, i);
    roboclaw.BackwardM2(address2, i);
    delay(50);    
  } 
}

void cbackward(){
  //test address 1 is right and address left is 2
  for(int i = 0; i <= 32; i++) {
    roboclaw.ForwardM1(address1, i);
    roboclaw.ForwardM2(address1, i);
    roboclaw.ForwardM1(address2, i);
    roboclaw.ForwardM2(address2, i);
    delay(50);    
  }
}

void cleft(){
  //test address 1 is right and address left is 2
  for(int i = 0; i <= 32; i++) {
    roboclaw.ForwardM1(address1, i);
    roboclaw.ForwardM2(address1, i);
    roboclaw.BackwardM1(address2, i);
    roboclaw.BackwardM2(address2, i);
    delay(50);    
  }
}

void cright(){
  //test address 1 is right and address left is 2
  for(int i = 0; i <= 32; i++) {
    roboclaw.ForwardM1(address2, i);
    roboclaw.ForwardM2(address2, i);
    roboclaw.BackwardM1(address1, i);
    roboclaw.BackwardM2(address1, i);
    delay(50);    
  }
}

void stop(){
  //test address 1 is right and address left is 2
  roboclaw.ForwardM1(address2, 0);
  roboclaw.ForwardM2(address2, 0);
  roboclaw.BackwardM1(address1, 0);
  roboclaw.BackwardM2(address1, 0);   
}
