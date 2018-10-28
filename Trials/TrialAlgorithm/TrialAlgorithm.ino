/*
  LED Distance Indicator

  created 24 Oct 2018
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
int state, stateCounter;

// Sampling
unsigned long lastReadSensor;
const int sensorSampleRate = 100;
unsigned long lastReadServo;
const int servoSampleRate = 2000;

void setup() {
  Serial.begin(9600); // open a serial connection to your computer

  // Pin assignment
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  //pinMode(bluePin, OUTPUT);
  myServo.attach(servoPin);
  myServo.write(0);

  // Initialization
  safeDistance = 180;
  state = 0;
  stateCounter = 350;
  
  delay(1000);
}

void loop() {
  if(millis() - lastReadSensor >= sensorSampleRate){
    
    distance = ultrasonic.distanceRead(); 

    // If object is further than safe distance,
    // decrease the safe distance and add to the state counter
    if( distance >= safeDistance ){
      if( safeDistance != 0){
        safeDistance--;
      } else{
        setColor(255,255,255);
      }
      if (stateCounter <= 349){
        stateCounter++;
      }
            
      Serial.print("All is good: "); Serial.print(distance); Serial.print(" & "); Serial.print(safeDistance); Serial.print("\n"); Serial.print("\n");
      
    }
    // If object is further than safe distance,
    // decrease the safe distance and subtract from the state counter
    else if ( distance < safeDistance) {
      if( safeDistance <= 179){
        safeDistance++;
      }
      if (stateCounter != 0){
        stateCounter--;
      }
       
      Serial.print("Nope: "); Serial.print(distance); Serial.print(" & "); Serial.print(safeDistance); Serial.print("\n"); Serial.print("\n");
      
    } else{
      Serial.print("Error");
    }
    lastReadSensor = millis();
  }

  if(millis() - lastReadServo >= servoSampleRate){
    // Map state counter value to one of the 6 states
    if ( stateCounter >= 300){
      state = 0;
    } else if ( stateCounter >= 250){
      state = 1;
    } else if ( stateCounter >= 200){
      state = 2;
    } else if ( stateCounter >= 150){
      state = 3;
    } else if ( stateCounter >= 100){
      state = 4;
    } else {
      state = 5;
    }

    // define angle and LED colour based on the state
    switch(state){
      // Very very happy
      case 0:
        angle = 15;
        colourR = 0;
        colourG = 255;
        colourB = 0;
        break;
      // Very happy
      case 1:
        angle = 45;
        colourR = 5;
        colourG = 150;
        colourB = 0;
        break;
      // Happy
      case 2:
        angle = 75;
        colourR = 10;
        colourG = 80;
        colourB = 0;
        break;
      // Angry
      case 3:
        angle = 105;
        colourR = 50;
        colourG = 50;
        colourB = 0;
        break;
      // Very Angry
      case 4:
        angle = 135;
        colourR = 150;
        colourG = 5;
        colourB = 0;
        break;
      // Very Angry
      case 5:
        angle = 165;
        colourR = 255;
        colourG = 0;
        colourB = 0;
        break;
    }

    // Set Servo angle
    myServo.write(angle);
    // Set LED colour
    setColor(colourR, colourG, colourB);
    
    lastReadServo = millis();
  }
}

void setColor(int red, int green, int blue){
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
