/*
Interface with a motor via the DRV8833 motor driver

Christopher Lum
lum@uw.edu

Version History
10/31/21: Created
11/01/21: Continued working
11/02/21: Continued working
*/

//Constants
int PinSLP    = 2;
int PinFLT    = 3;

int PinAIN1   = 5;
int PinAIN2   = 6;
int PinBIN1   = 10;
int PinBIN2   = 11;

void setup() {
  //Serial
  Serial.begin(9600);

  //Pins
  pinMode(PinSLP,OUTPUT);
  pinMode(PinFLT,INPUT);
  pinMode(PinAIN1,OUTPUT);
  pinMode(PinAIN2,OUTPUT);
  pinMode(PinBIN1,OUTPUT);
  pinMode(PinBIN2,OUTPUT);
  
}

void loop() {
  //User selections
  int delayTime_ms = 2000;

  //-------
  //Motor A
  //-------
  Serial.println("Motor A");

  //enable DRV8833 chip
  Serial.println("Enabling DRV8833");
  digitalWrite(PinSLP,HIGH);
  
  //spin motor in various states
  Serial.println("Spin forward");
  digitalWrite(PinAIN1,HIGH); 
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);
  
  Serial.println("Spin backwards");
  digitalWrite(PinAIN1,LOW); 
  digitalWrite(PinAIN2,HIGH);
  delay(delayTime_ms);

  Serial.println("Stop");
  digitalWrite(PinAIN1,LOW); 
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);

  //spin motor forwards at varying speeds
  Serial.println("PWM = 100");
  analogWrite(PinAIN1,100);
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);

  Serial.println("PWM = 150");
  analogWrite(PinAIN1,150);
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);

  Serial.println("PWM = 200");
  analogWrite(PinAIN1,200);
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);

  Serial.println("PWM = 250");
  analogWrite(PinAIN1,250);
  digitalWrite(PinAIN2,LOW);
  delay(delayTime_ms);

  //disable using the SLP pin
  digitalWrite(PinAIN1,HIGH); 
  digitalWrite(PinAIN2,LOW);
  delay(1000);
  Serial.println("Disable via SLP pin");
  digitalWrite(PinSLP,LOW);
  delay(1000);

  Serial.println("Stop");
  digitalWrite(PinAIN1,LOW); 
  digitalWrite(PinAIN2,LOW);
  
  Serial.println("");

  //-------
  //Motor B
  //-------
  Serial.println("Motor B");

  //enable DRV8833 chip
  Serial.println("Enabling DRV8833");
  digitalWrite(PinSLP,HIGH);
  
  //spin motor in various states
  Serial.println("Spin forward");
  digitalWrite(PinBIN1,HIGH); 
  digitalWrite(PinBIN2,LOW);
  delay(delayTime_ms);

  Serial.println("Spin backwards");
  digitalWrite(PinBIN1,LOW); 
  digitalWrite(PinBIN2,HIGH);
  delay(delayTime_ms);

  Serial.println("Stop");
  digitalWrite(PinBIN1,LOW); 
  digitalWrite(PinBIN2,LOW);
  delay(delayTime_ms);

  //spin motor forwards at varying speeds
  Serial.println("PWM = 100");
  analogWrite(PinBIN1,100);
  digitalWrite(PinBIN2,LOW);
  delay(delayTime_ms);

  Serial.println("PWM = 150");
  analogWrite(PinBIN1,150);
  digitalWrite(PinBIN2,LOW);
  delay(delayTime_ms);

  Serial.println("PWM = 200");
  analogWrite(PinBIN1,200);
  digitalWrite(PinBIN2,LOW);
  delay(delayTime_ms);

  Serial.println("PWM = 250");
  analogWrite(PinBIN1,250);
  digitalWrite(PinBIN2,LOW);
  delay(delayTime_ms);

  //disable using the SLP pin
  digitalWrite(PinBIN1,HIGH); 
  digitalWrite(PinBIN2,LOW);
  delay(1000);
  Serial.println("Disable via SLP pin");
  digitalWrite(PinSLP,LOW);
  delay(1000);

  Serial.println("Stop");
  digitalWrite(PinBIN1,LOW); 
  digitalWrite(PinBIN2,LOW);

  Serial.println("");
}
