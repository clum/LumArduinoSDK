/*
Control an external RGB LED and make it blink using digitalWrite.

Christopher Lum
lum@uw.edu

Version History
10/27/21: created
11/11/21: Updated
*/

//Constants
int PinLED_R = A5;
int PinLED_G = A4;
int PinLED_B = A3;

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
  digitalWrite(PinLED_R,HIGH);
  delay(300);
  digitalWrite(PinLED_R,LOW);
  delay(300);

  digitalWrite(PinLED_G,HIGH);
  delay(300);
  digitalWrite(PinLED_G,LOW);
  delay(300);

  digitalWrite(PinLED_B,HIGH);
  delay(300);
  digitalWrite(PinLED_B,LOW);
  delay(300);
}
