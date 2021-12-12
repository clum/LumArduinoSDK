/*
Similar to HCSR04_01_Simple.ino except this refactors much of the code to a library.

Christopher Lum
lum@uw.edu

Version History
12/12/21: created
*/

#include "LumHCSR04.h"

//Constants
int PinHCS04Trigger   = 4;
int PinHCS04Echo      = 5;

void setup() {
  //Serial
  Serial.begin(9600);
  
  //HC-SR04
  pinMode(PinHCS04Trigger,OUTPUT);
  pinMode(PinHCS04Echo,INPUT);
}

void loop() {
  unsigned long timeout = 100000;
  int distance_cm = HCSR04GetDistance_cm(PinHCS04Trigger, PinHCS04Echo, timeout);
  
  Serial.println("distance_cm = "+(String)distance_cm);  
}
