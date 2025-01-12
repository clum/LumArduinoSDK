/*
Control a single external LED and make it blink using digitalWrite.  The LED is powered through the IRFZ44N.

Notes:
  -LED should be in series with a current limiting resistor (500 - 1000 ohms).
  -LED should have long leg to pin and short leg closer to ground.
  -Arduino Nano built in LED is on pin D13 (or use LED_BUILTIN)

Christopher Lum
lum@uw.edu

Version History
01/10/25: Created
*/

//Constants
int PinLED_R = A4;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_R,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PinLED_R,HIGH);
  delay(500);
  digitalWrite(PinLED_R,LOW);
  delay(500);
}
