/*
Control an external RGB LED using a transistor.

For more info see https://www.makeuseof.com/tag/connect-led-light-strips-arduino/

Christopher Lum
lum@uw.edu

Version History
11/18/21: created
*/

//Constants
int PinLED_R = 9;
int PinLED_G = 10;
int PinLED_B = 11;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_R,OUTPUT);
  pinMode(PinLED_G,OUTPUT);
  pinMode(PinLED_B,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  int red = 255;
  int green = 79;
  int blue = 39;

  analogWrite(PinLED_R,red);
  analogWrite(PinLED_B,green);
  analogWrite(PinLED_G,blue);    
}
