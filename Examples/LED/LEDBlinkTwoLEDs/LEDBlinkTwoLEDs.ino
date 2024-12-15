/*
Control two external LED and make it blink using digitalWrite.

Notes:
  -Each LED should be in series with a current limiting resistor (500 - 1000 ohms).
  -LED should have long leg to pin and short leg closer to ground.
  -Arduino Nano built in LED is on pin D13 (or use LED_BUILTIN)

Christopher Lum
lum@uw.edu

Version History
12/04/21: created
04/28/22: Added note about current limiting resistor
09/10/24: Added note about LED directionality and changed blink duration to differentiate between LEDs
12/14/24: Changed default pins (from A4 and A5)
*/

//Constants
int PinLED_R = 6;
int PinLED_G = 5;

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
  delay(1000);
  digitalWrite(PinLED_R,LOW);
  delay(300);

  digitalWrite(PinLED_G,HIGH);
  delay(300);
  digitalWrite(PinLED_G,LOW);
  delay(300);
}
