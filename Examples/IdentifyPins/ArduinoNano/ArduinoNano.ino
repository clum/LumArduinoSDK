/*
Identify the pin numbers on the Arduino Nano.

This is designed to be used with the Arduino setup with LEDs setup on pins 2 - 21 to allow you to see the results/outputs.

See https://www.makerguides.com/arduino-nano/

Christopher Lum
lum@uw.edu

Version History
11/13/21: created
12/14/24: added choice of how to refer to pins.  Added documentation.
*/

//Constants
int onTime_ms = 2000;

//Digital pins are only defined using numbers (no enums or #defines like analog pins)
int PinD02 = 2;
int PinD03 = 3;
int PinD04 = 4;
int PinD05 = 5;
int PinD06 = 6;
int PinD07 = 7;
int PinD08 = 8;
int PinD09 = 9;
int PinD10 = 10;
int PinD11 = 11;
int PinD12 = 12;
int PinD13 = 13;

//Analog pins can be referenced to either numbers or enums/defines
//
//  Enum  number  comment
//  ----  ------  -------
//  A0    14
//  A1    15
//  A2    16
//  A3    17
//  A4    18
//  A5    19
//  A6    20  read only, does not appear it can be used as a digital output (no results)
//  A7    21  read only, appears to be able to be made as a digital output but when this goes high it outputs to pin 8 and 10 (not to pin 21)

/*
//Reference pins using enums
int PinA0 = A0;
int PinA1 = A1;
int PinA2 = A2;
int PinA3 = A3;
int PinA4 = A4;
int PinA5 = A5;
int PinA6 = A6;
int PinA7 = A7;
*/

//Reference pins using numbers
int PinA0 = 14;
int PinA1 = 15;
int PinA2 = 16;
int PinA3 = 17;
int PinA4 = 18;
int PinA5 = 19;
int PinA6 = 20;
int PinA7 = 21;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinD02,OUTPUT);
  pinMode(PinD03,OUTPUT);
  pinMode(PinD04,OUTPUT);
  pinMode(PinD05,OUTPUT);
  pinMode(PinD06,OUTPUT);
  pinMode(PinD07,OUTPUT);
  pinMode(PinD08,OUTPUT);
  pinMode(PinD09,OUTPUT);
  pinMode(PinD10,OUTPUT);
  pinMode(PinD11,OUTPUT);
  pinMode(PinD12,OUTPUT);
  pinMode(PinD13,OUTPUT);
  
  pinMode(PinA0,OUTPUT);
  pinMode(PinA1,OUTPUT);
  pinMode(PinA2,OUTPUT);
  pinMode(PinA3,OUTPUT);
  pinMode(PinA4,OUTPUT);
  pinMode(PinA5,OUTPUT);
  pinMode(PinA6,OUTPUT);
  pinMode(PinA7,OUTPUT);
}

void loop() {
  Serial.println("D Pins");

  turnPinOn(PinD02,onTime_ms);
  turnPinOn(PinD03,onTime_ms);
  turnPinOn(PinD04,onTime_ms);
  turnPinOn(PinD05,onTime_ms);
  turnPinOn(PinD06,onTime_ms);
  turnPinOn(PinD07,onTime_ms);
  turnPinOn(PinD08,onTime_ms);
  turnPinOn(PinD09,onTime_ms);  
  turnPinOn(PinD10,onTime_ms);
  turnPinOn(PinD11,onTime_ms);
  turnPinOn(PinD12,onTime_ms);
  turnPinOn(PinD13,onTime_ms);
  
  Serial.println("A pins");
  turnPinOn(PinA0,onTime_ms);
  turnPinOn(PinA1,onTime_ms);
  turnPinOn(PinA2,onTime_ms);
  turnPinOn(PinA3,onTime_ms);
  turnPinOn(PinA4,onTime_ms);
  turnPinOn(PinA5,onTime_ms);
  turnPinOn(PinA6,onTime_ms);
  turnPinOn(PinA7,onTime_ms);
}

void turnPinOn(int pin,int onTime_ms) {
  Serial.println("Turning on pin: " + (String)pin);
  digitalWrite(pin,HIGH);
  delay(onTime_ms);
  digitalWrite(pin,LOW);
}
