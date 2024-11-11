/*
Generate a clock signal that can be used for SSI operations.

Notes:
  -Each LED should be in series with a current limiting resistor (500 - 1000 ohms).
  -LED should have long leg to pin and short leg closer to ground.
  -Arduino Nano built in LED is on pin D13 (or use LED_BUILTIN)

Christopher Lum
lum@uw.edu

Version History
11/11/24: created
*/

//Constants
int PinLED_R = 7;
int PinLED_G = 8;

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
  delay(500);
  digitalWrite(PinLED_R,LOW);
  delay(100);

  digitalWrite(PinLED_G,HIGH);
  delay(100);
  digitalWrite(PinLED_G,LOW);
  delay(100);
}
