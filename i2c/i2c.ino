#include <Wire.h>

#define SLAVE_ADDRESS 0x08

// Movement bytes
#define MOVEMENT 0x00
#define FORWARD 0x00
#define BACKWARD 0x01

// Claw bytes
#define CLAW 0x01

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
      Serial.println("Type: Movement")
      if (incomingData[1] == FORWARD) {
        Serial.println("Direction: Forward");
      }
      else if (incomingData[1] == BACKWARD) {
        Serial.println("Direction: Backward");
      }
      else {
        Serial.println("Direction: Unknown")
      }

      Serial.println("Speed: " + incomingData[2])
      
      break;
    case CLAW:
      // there will be something idk
      Serial.print("Type: Claw")

      break;
    default:
      break;

  }
  switch(incomingData[1]) {
    case MOVEMENT:
      // there will be a direction and a speed
      Serial.print("Type: Movement")
      
      break;
    case CLAW:
      // there will be something idk
      Serial.print("Claw")

      break;
    default:
      break;

  }

}

void sendData()
{
  Wire.write(data_to_echo);
}

void setup() 
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() { 
  if(command_finished){
    if(data_to_echo == 'f') // Forward
    {
      Serial.println("Forward");
    } else if(data_to_echo == 'b')
    {
      Serial.println("Backward");
    } else if(data_to_echo == 'l')
    {
      Serial.println("Left");
    } else if(data_to_echo =='r'){
      Serial.println("Right");
    }
    else if(data_to_echo == 's')
    {
      Serial.println("Uni Stop");
    } else if(data_to_echo == 'F')
    {
      Serial.println("Timed F");
    } else if(data_to_echo =='B'){
      Serial.println("Timed Back");
    } else if(data_to_echo == 'L')
    {
      Serial.println("Timed Left");
    } else if(data_to_echo == 'R')
    {
      Serial.println("Timed Right");
    } else if(data_to_echo =='p')
    {
      Serial.println("Auger Foward");
    } else if(data_to_echo == 'o')
    {
      Serial.println("Auger Backward");
    } else if(data_to_echo == 'S')
    {
      Serial.println("Auger Stop");
    } else if(data_to_echo =='c')
    {
      Serial.println("Drill CC");
    } else if(data_to_echo == 'w')
    {
      Serial.println("Drill CCW");
    } else if(data_to_echo == 'D')
    {
      Serial.println("Drill Stop");
    } else if(data_to_echo =='u')
    {
      Serial.println("Lin Act Up");
    } else if(data_to_echo == 'd')
    {
      Serial.println("Lin Act Down");
    } else if(data_to_echo == 'A')
    {
      Serial.println("Lin Act Stop");
    } else {
      Serial.println("No Command");
    }
  }
}
