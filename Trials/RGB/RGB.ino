/*
  LED Distance Indicator

  created 21 Oct 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>
#include <Servo.h>

// Pins
#define bluePin 4
#define greenPin 5
#define redPin 6
#define usEchoPin 7
#define usTrigPin 8
#define servoPin 9

// Objects
Ultrasonic ultrasonic(usTrigPin, usEchoPin);
Servo myServo;

// Global Variables
int angle;            // Angle for the servo motor
int distance;         // Distance of closest object
int safeDistance;     // Safe distance
int colourR, colourG, colourB;

// SampleRate
unsigned long lastRead;   // used for the sampleRate timer
int sampleRate = 100;     // the sampleRate for reading the sensor

void setup() {
  Serial.begin(9600); // open a serial connection to your computer

  // Assign pin mode
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  myServo.attach(servoPin);
  myServo.write(0);
  
  safeDistance = 180;
  
  delay(1000);
}

void loop() {
  if(millis() - lastRead >= sampleRate){
    // Set servo angle as the safe distance
    angle = safeDistance;
    myServo.write(angle);

    distance = ultrasonic.distanceRead(); 

    // If object is further than safe distance,
    // turn LED green and decrease safe distance
    if( distance >= safeDistance ){
      if( safeDistance != 0){
        safeDistance--;
      }
      // RGB LED TO GREEN
      setColor(0, 255, 0);
      
      Serial.print("All is good: ");
      Serial.print(distance);
      Serial.print(" & ");
      Serial.print(safeDistance);
      Serial.print("\n");
      Serial.print("\n");
      
    } 
    // If object is closer than safe distance,
    // turn LED red and increase safe distance
    else if ( distance < safeDistance) {
      if( safeDistance <= 179){
        safeDistance++;
      }
      // RGB LED TO RED
      setColor(255, 0, 0);
      
      Serial.print("Nope: ");
      Serial.print(distance);
      Serial.print(" & ");
      Serial.print(safeDistance);
      Serial.print("\n");
      Serial.print("\n");
      
    } else{
      Serial.print("Error");
    }
    lastRead = millis();
  }
}

void setColor(int red, int green, int blue){
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
