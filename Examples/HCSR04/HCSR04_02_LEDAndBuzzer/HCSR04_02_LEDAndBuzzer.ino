/*
Activate LEDs and buzzer based on the distance measured by the HC-SR04 sensor.

Christopher Lum
lum@uw.edu

Version History
11/17/21: created
*/

#include "pitches.h"

//Constants
int PinHCS04Trigger   = 4;
int PinHCS04Echo      = 5;

int PinLED_R          = A5;
int PinLED_G          = A4;
int PinLED_B          = A3;

int PinBuzzer         = 8;

int toneDuration_ms   = 100;

void setup() {
  //Serial
  Serial.begin(9600);
  
  //HC-SR04
  pinMode(PinHCS04Trigger,OUTPUT);
  pinMode(PinHCS04Echo,INPUT);

  //LED
  pinMode(PinLED_R,OUTPUT);
  pinMode(PinLED_G,OUTPUT);
  pinMode(PinLED_B,OUTPUT);

  //Buzzer
  pinMode(PinBuzzer,OUTPUT);
}

void loop() {
  //set HC-S04 trigger to low
  digitalWrite(PinHCS04Trigger,LOW);
  delayMicroseconds(2);

  //set HC-S04 trigger to high for 10 microseconds to initiate a pulse
  digitalWrite(PinHCS04Trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(PinHCS04Trigger,LOW);

  //obtain the response from the echo pin
  long duration_ms = pulseIn(PinHCS04Echo,HIGH);

  //convert to distance
  int distance_cm = duration_ms*0.034/2;  

  //LEDS
  if(distance_cm >= 13) {
    //blue: long distance
    digitalWrite(PinLED_R,LOW);
    digitalWrite(PinLED_G,LOW);
    digitalWrite(PinLED_B,HIGH);

    tone(PinBuzzer,NOTE_C4,toneDuration_ms);
          
  } else if(distance_cm < 13 && distance_cm >= 5) {
    //green: medium
    digitalWrite(PinLED_R,LOW);
    digitalWrite(PinLED_G,HIGH);
    digitalWrite(PinLED_B,LOW);

    tone(PinBuzzer,NOTE_E4,toneDuration_ms);    
    
  } else {
    //red: near
    digitalWrite(PinLED_R,HIGH); 
    digitalWrite(PinLED_G,LOW);
    digitalWrite(PinLED_B,LOW);

    tone(PinBuzzer,NOTE_G4,toneDuration_ms);    
    
  }
  
  Serial.println("distance_cm = "+(String)distance_cm);  
}
