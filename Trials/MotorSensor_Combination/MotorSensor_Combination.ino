/*
  LED Distance Indicator

  created 21 Oct 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>
#include <Servo.h>

// Pins
#define servoPin 12
#define usTrigPin 11
#define usEchoPin 10

// Objects
Ultrasonic ultrasonic(usTrigPin, usEchoPin);
Servo myServo;

int angle;     // Angle for the servo motor
int distance;  // Distance of closest object


void setup() {
  Serial.begin(9600); // open a serial connection to your computer

  myServo.attach(servoPin);
  angle = 0;
  myServo.write(angle);
  
  delay(1000);
}

void loop() {
  distance = ultrasonic.distanceRead();

  // Check for distance and assign an angle base on that
  if (distance >= 60){
    angle = 15;
    myServo.write(angle);
  } else if (distance >= 50){
    angle = 45;
    myServo.write(angle);
  } else if (distance >= 40){
    angle = 75;
    myServo.write(angle);
  } else if (distance >= 30){
    angle = 105;
    myServo.write(angle);
  } else if (distance >= 20){
    angle = 135;
    myServo.write(angle);
  } else{
    angle = 165;
    myServo.write(angle);
  }
  
  // wait for the servo to get there
  delay(2500);
  
  Serial.print(angle);
  Serial.print("\t");
  Serial.print(distance);
  Serial.print("\n");
}
