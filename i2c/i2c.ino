#include <Wire.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

#define SLAVE_ADDRESS 0x08

#define address1 0x80
#define address2 0x81

// Movement bytes
#define MOVEMENT 0x00
#define FORWARD 0x01
#define BACKWARD 0x02
#define LEFT 0x03
#define RIGHT 0x04
#define STOP 0x05

SoftwareSerial serial(10,11);
RoboClaw roboclaw(&serial,10000);

bool command_finish = true;

void startMotor(int direction, int speed) {
  Serial.println(direction);
  switch(direction) {
    case FORWARD:
      for(int i = 0; i <= speed; i++) {
        roboclaw.BackwardM1(address1, i);
        roboclaw.BackwardM2(address1, i);
        roboclaw.BackwardM1(address2, i);
        roboclaw.BackwardM2(address2, i);
        delay(50); 
      }  
      break;
    case BACKWARD:
      for(int i = 0; i <= speed; i++) {
        roboclaw.ForwardM1(address1, i);
        roboclaw.ForwardM2(address1, i);
        roboclaw.ForwardM1(address2, i);
        roboclaw.ForwardM2(address2, i);
        delay(50);    
      }
      break;
    case LEFT:
      for(int i = 0; i <= speed; i++) {
        roboclaw.ForwardM1(address1, i);
        roboclaw.ForwardM2(address1, i);
        roboclaw.BackwardM1(address2, i);
        roboclaw.BackwardM2(address2, i);
        delay(50);    
      }
      break;
    case RIGHT:
      for(int i = 0; i <= speed; i++) {
        roboclaw.ForwardM1(address2, i);
        roboclaw.ForwardM2(address2, i);
        roboclaw.BackwardM1(address1, i);
        roboclaw.BackwardM2(address1, i);
        delay(50);    
      }
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

void receiveData(int byteCount)
{
  Serial.print("BYTE COUNT: ");
  Serial.println(byteCount);
  int incomingData[byteCount];
  for (int i = 0; i < byteCount; i++) {
    incomingData[i] = Wire.read();
  }

  if (incomingData[2] > 30) {
    Serial.println("Overspeed");
    return;
  }

  startMotor(incomingData[1], incomingData[2]);

}

void loop() {

}

void setup() 
{
  roboclaw.begin(38400);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}