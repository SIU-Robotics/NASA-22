#include <Wire.h>
#define SLAVE_ADDRESS 0x08
byte data_to_echo = 0;

boolean command_finish = true;

void receiveData(int bytecount)
{
  Serial.print("BYTE COUNT: ");
  Serial.println(bytecount);
  for (int i = 0; i < bytecount; i++) {
    data_to_echo = Wire.read();
    if(data_to_echo == 'f'){
      Serial.println(data_to_echo == 'f');
    } else {
      Serial.println("Not correct");
    }
    
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
