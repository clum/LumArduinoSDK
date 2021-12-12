/*
Identify the pin numbers on the Arduino Nano.

See https://www.makerguides.com/arduino-nano/
Christopher Lum
lum@uw.edu

Version History
11/13/21: created
*/

//Constants

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

int PinA0 = A0; //AKA pin 14
int PinA1 = A1; //AKA pin 15
int PinA2 = A2; //AKA pin 16
int PinA3 = A3; //AKA pin 17
int PinA4 = A4; //AKA pin 18
int PinA5 = A5; //AKA pin 19
int PinA6 = A6; //AKA pin 20 (read only)
int PinA7 = A7; //AKA pin 21 (read only).  When this goes high it does not output to pin 21 but outputs to pins 8 and 10


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
  int flashTime_ms = 1500;
  Serial.println("D Pins");
  flashPin(PinD02,flashTime_ms);
  flashPin(PinD03,flashTime_ms);
  flashPin(PinD04,flashTime_ms);
  flashPin(PinD05,flashTime_ms);
  flashPin(PinD06,flashTime_ms);
  flashPin(PinD07,flashTime_ms);
  flashPin(PinD08,flashTime_ms);
  flashPin(PinD09,flashTime_ms);  
  flashPin(PinD10,flashTime_ms);
  flashPin(PinD11,flashTime_ms);
  flashPin(PinD12,flashTime_ms);
  flashPin(PinD13,flashTime_ms);
  
  Serial.println("A pins");
  flashPin(PinA0,flashTime_ms);
  flashPin(PinA1,flashTime_ms);
  flashPin(PinA2,flashTime_ms);
  flashPin(PinA3,flashTime_ms);
  flashPin(PinA4,flashTime_ms);
  flashPin(PinA5,flashTime_ms);
  flashPin(PinA6,flashTime_ms);
  flashPin(PinA7,flashTime_ms);
}

void flashPin(int pin,int flashTime_ms) {
  Serial.println("Flashing pin: " + (String)pin);
  digitalWrite(pin,HIGH);
  delay(flashTime_ms);
  digitalWrite(pin,LOW);
}
