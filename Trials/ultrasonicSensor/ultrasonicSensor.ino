/*
  Ultrasonic Sensor

  created 21 Oct 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>

// Pin 11 as Trig
// Pin 10 as Echo

Ultrasonic ultrasonic(10, 11);

void setup() {
  Serial.begin(9600); // open a serial connection to your computer
}

void loop() {

  Serial.print("Distance in CM: ");
  Serial.println(ultrasonic.distanceRead());
  Serial.print("Distance in INC: ");
  Serial.println(ultrasonic.distanceRead(INC));
  delay(1000);
}
