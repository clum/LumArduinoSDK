/*
Control two external LED and make it blink using digitalWrite.

Note that each LED should be in series with a current limiting resistor (500 - 1000 ohms).

Christopher Lum
lum@uw.edu

Version History
12/04/21: created
04/28/22: Added note about current limiting resistor
*/

//Constants
int PinLED_R = A4;
int PinLED_G = A5;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_R,OUTPUT);
  pinMode(PinLED_G,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PinLED_R,HIGH);
  delay(300);
  digitalWrite(PinLED_R,LOW);
  delay(300);

  digitalWrite(PinLED_G,HIGH);
  delay(300);
  digitalWrite(PinLED_G,LOW);
  delay(300);
}
