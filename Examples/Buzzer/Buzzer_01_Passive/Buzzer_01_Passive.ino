/*
Control passive buzzer.

Christopher Lum
lum@uw.edu

Version History
03/21/22: created
*/

int PinBuzzer = 9;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //Buzzer
  pinMode(PinBuzzer,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  tone(PinBuzzer, 1000);
  delay(1000);
  noTone(PinBuzzer);
  delay(1000);
}
