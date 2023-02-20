  // Motor A connections
int enA = 10;
int in1 = 2;
int in2 = 4;
// Motor B connections
int enB = 11;
int in3 = 7;
int in4 = 8;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

//  MAIN LOOP currently empty :(
void loop() {
}

/* Below are basic functions for controlling motors
Currently only two motors can be controlled but easy enough
to expand. Any questions on what is going on please contact 
someone from software arduino. If youd like to add functions,
please feel free to :) just dont mess with what is currently here.
The acceleration/decceleration function is still under 
development */

//  Turn motors on in forward direction
void motorOnForward() {
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
}

//  Turn motors on in backwards direction
void motorOnBackward() {
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
}

//  Turn off motors
void motorsOff() {
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

//  Control direction of individual motors
void directionControl(int motorNumber) {
  //Checks which motor is being addressed and changes direction
  switch(motorNumber) {
    case 1:
      if (digitalRead(in1) == HIGH) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
      }
      else {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);     
      }
    break;
    case 2:
      if (digitalRead(in3) == HIGH) {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }
      else {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);     
      }
    break; 
  }
}

//  Controls speed of all motors
void speedControl(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

//  Control speed of individual motors
void directionControl(int motorNumber, int speed) {
  //Checks which motor is being addressed and changes direction
  switch(motorNumber) {
    case 1:
      analogWrite(enA, speed);
    break;
    case 2:
      analogWrite(enB, speed);
    break; 
  }
}

//  Accelerate/Deccelerate all motors
void accelearateAll(int speed) {
  if (speed < analogRead(enA) && speed < analogRead(enB)) {
	  for (int i = analogRead(enA); i < speed; i++) {
		  analogWrite(enA, i);
		  analogWrite(enB, i);
		  delay(20);
	  }
  }
  else {
    for (int i = analogRead(enA); i >= speed; --i) {
		  analogWrite(enA, i);
		  analogWrite(enB, i);
		  delay(20);
	  }
  }
}


