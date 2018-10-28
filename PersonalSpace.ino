/*
  Personal Space

  created 25 Oct 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>
#include <Servo.h>

// Pins
#define servoPin 12
#define usTrigPin 11
#define usEchoPin 10
#define En1 9
#define InA1 8
#define InB1 7
#define En2 6
#define InA2 5
#define InB2 4

// Objects
Ultrasonic ultrasonic(usTrigPin, usEchoPin);
Servo myServo;

// Global Variables
int angle;                         // Angle for the servo motor
int distance;                      // Distance of closest object
int safeDistance;                  // Safe distance
int currentState, previousState;   // Keep track of status

// Sampling
unsigned long lastRead;
const int sampleRate = 250;

void setup() {
  Serial.begin(9600); // open a serial connection to your computer

  // Pin assignment
  myServo.attach(servoPin);
  myServo.write(90);

  pinMode(En1, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(En2, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
  
  digitalWrite(InA2,HIGH);
  digitalWrite(InB2,LOW);
  digitalWrite(InA1,HIGH);
  digitalWrite(InB1,LOW);  
  
  safeDistance = 180;
  angle = 90;
  previousState = 0;
  currentState = 0;

  delay(5000);
}

void loop() {
  
  if(millis() - lastRead >= sampleRate){
    // Read distance
    distance = ultrasonic.distanceRead(); 

    // if object is closer than safeDistance
    // reduce the safeDitance
    if( distance >= safeDistance ){
      // While safeDistance is not zero, reduce the safeDistance
      Serial.print("YES ");
      previousState = currentState;
      currentState = 0;
      if( safeDistance >= 1){
        safeDistance--;
      } else{
        setup();
      }
    } 
    // if object is further than safeDistance
    // increase the safeDitance
    else if ( distance < safeDistance) {
      Serial.print("No ");
      previousState = currentState;
      currentState = 1;
      if( safeDistance <= 179){
        safeDistance++;
      }
    } 
    else{
      Serial.print("Error");
    }

    /*
     * Ideal Case if a stron enough fan is being used
     * the fan should only turn on inflating when the status changes
        
        // Bag Status
        // If you move into the personal space 
        // inflate the bag
        if ( currentState - previousState == 1){
          digitalWrite(En1,LOW);
          digitalWrite(En2,HIGH);
          delay(1000);
        } 
        // else deflate the bag
        else {
          digitalWrite(En1,HIGH);
          digitalWrite(En2,LOW);
        }    
    */

    // Set angle for the servo
    // Reset angle to 90 degree when status changes
    if ( currentState != previousState){
      angle = 90;
    }
    // if object is not in personal space
    // add to the angle and start deflation
    if ( currentState == 1 ){
      if( angle <= 179){
        angle++;
        digitalWrite(En1,LOW);
        digitalWrite(En2,HIGH);
      }
    } 
    // if object is in personal space
    // reduce from the angle and start inflation
    else {
      if (angle >= 1){
        angle = angle - 1;
        digitalWrite(En1,HIGH);
        digitalWrite(En2,LOW);
      }
    }
    // Set the angle to the servo
    myServo.write(angle);

    Serial.print(distance); Serial.print(" & "); Serial.print(safeDistance); Serial.print("\n"); Serial.print("\n");
    
    lastRead = millis();
  }
}
