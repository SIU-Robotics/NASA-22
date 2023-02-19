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
      Serial.println("Type: Movement");
      if (incomingData[1] == FORWARD) {
        Serial.println("Direction: Forward");
       for(int i = 0; i <= 32; i++) {
          roboclaw.BackwardM1(address1, i);
          roboclaw.BackwardM2(address1, i);
          roboclaw.BackwardM1(address2, i);
          roboclaw.BackwardM2(address2, i);
          delay(50); 
       }        
      }
      else if (incomingData[1] == BACKWARD) {
        Serial.println("Direction: Backward");
        for(int i = 0; i <= 32; i++) {
          roboclaw.ForwardM1(address1, i);
          roboclaw.ForwardM2(address1, i);
          roboclaw.ForwardM1(address2, i);
          roboclaw.ForwardM2(address2, i);
          delay(50);    
        }
      }
      else if (incomingData[1] == LEFT) {
        Serial.println("Direction: Left");
        for(int i = 0; i <= 32; i++) {
          roboclaw.ForwardM1(address1, i);
          roboclaw.ForwardM2(address1, i);
          roboclaw.BackwardM1(address2, i);
          roboclaw.BackwardM2(address2, i);
          delay(50);    
        }
      }
      else if (incomingData[1] == RIGHT) {
        Serial.println("Direction: Right");
        for(int i = 0; i <= 32; i++) {
          roboclaw.ForwardM1(address2, i);
          roboclaw.ForwardM2(address2, i);
          roboclaw.BackwardM1(address1, i);
          roboclaw.BackwardM2(address1, i);
          delay(50);    
        }
      }
      else if (incomingData[1] == STOP) {
        Serial.println("Direction: Stop");
        roboclaw.ForwardM1(address2, 0);
        roboclaw.ForwardM2(address2, 0);
        roboclaw.BackwardM1(address1, 0);
        roboclaw.BackwardM2(address1, 0); 
      }        
      else {
        Serial.println("Direction: Unknown");
      }

      Serial.println("Speed: " + incomingData[2]);
      
      break;
    default:
      break;

  }
  switch(incomingData[1]) {
    case MOVEMENT:
      // there will be a direction and a speed
      Serial.print("Type: Movement");
      
      break;
    default:
      break;

  }

}


void setup() 
{
  roboclaw.begin(38400);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}