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
  flash();
  pulse();

  delay(1000);
}

void flash() {
  int delay_ms = 150;
  
  //flash red
  digitalWrite(PinLED_R,HIGH);
  delay(delay_ms);
  digitalWrite(PinLED_R,LOW);
  delay(delay_ms);

  //flash green  
  digitalWrite(PinLED_G,HIGH);
  delay(delay_ms);
  digitalWrite(PinLED_G,LOW);
  delay(delay_ms);

  //flash blue  
  digitalWrite(PinLED_B,HIGH);
  delay(delay_ms);
  digitalWrite(PinLED_B,LOW);
  delay(delay_ms);
}

void pulse() {
  int delay_ms = 5;

  //pulse red
  for(int i = 0; i < 256; i++) {
    analogWrite(PinLED_R,i);
    delay(delay_ms);    
  }

  for(int i = 255; i >=0; i--) {
    analogWrite(PinLED_R,i);
    delay(delay_ms);    
  }

  //pulse green
  for(int i = 0; i < 256; i++) {
    analogWrite(PinLED_G,i);
    delay(delay_ms);    
  }

  for(int i = 255; i >=0; i--) {
    analogWrite(PinLED_G,i);
    delay(delay_ms);    
  }

  //pulse blue
  for(int i = 0; i < 256; i++) {
    analogWrite(PinLED_B,i);
    delay(delay_ms);    
  }

  for(int i = 255; i >=0; i--) {
    analogWrite(PinLED_B,i);
    delay(delay_ms);    
  }
}
