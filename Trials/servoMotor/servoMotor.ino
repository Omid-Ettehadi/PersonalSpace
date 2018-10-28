/*
  Servo Motor

  created 19 Oct 2018
  by Omid Ettehadi
*/

// Libraries
#include <Servo.h>

// Objects
Servo myServo;

// variable to hold the angle for the servo motor
int angle;   

void setup() {
  Serial.begin(9600); // open a serial connection to your computer
  
  myServo.attach(12); // attaches the servo on pin 12 to the servo object
  angle = 15;
  myServo.write(angle);
  
  delay(1000);
}

void loop() {
  Serial.print(angle);
  Serial.print("\n");
  
  // set the servo position
  myServo.write(angle);

  // Add to the angle until you reach 165 then restart
  if(angle == 165){
    angle = 15;
  } else{
    angle = angle + 30;
  }
  
  // wait for the servo to get there
  delay(2500);
}
