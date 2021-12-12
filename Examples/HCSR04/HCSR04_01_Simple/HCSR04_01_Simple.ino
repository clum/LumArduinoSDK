/*
Simple example to show how to interface with the HC-SR04 sensor.

See https://www.youtube.com/watch?v=ZejQOX69K5M for more information.

Christopher Lum
lum@uw.edu

Version History
11/17/21: created
12/12/21: refactored function naming
*/

//Constants
int PinHCS04Trigger   = 4;
int PinHCS04Echo      = 5;

void setup() {
  //Serial
  Serial.begin(9600);
  
  //HC-SR04
  pinMode(PinHCS04Trigger,OUTPUT);
  pinMode(PinHCS04Echo,INPUT);
}

void loop() {
  //set HC-S04 trigger to low
  digitalWrite(PinHCS04Trigger,LOW);
  delayMicroseconds(2);

  //set HC-S04 trigger to high for 10 microseconds to initiate a pulse
  digitalWrite(PinHCS04Trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(PinHCS04Trigger,LOW);

  //obtain the response from the echo pin
  long timeOfFlight_microseconds = pulseIn(PinHCS04Echo,HIGH);

  //convert to distance
  int distance_cm = timeOfFlight_microseconds*0.034/2;  
  
  Serial.println("distance_cm = "+(String)distance_cm);  
}
