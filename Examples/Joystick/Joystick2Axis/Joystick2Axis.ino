/*
Interface with a 2 axis joystick.

Note that this joystick also has a button/switch which activates when you press down on it.

See https://youtu.be/B6YEQj4d5WU for tutorial and discussion.

Christopher Lum
lum@uw.edu

Version History
10/27/21: created
11/11/21: Updated
*/

//Constants
int PinX    = A0;   //analog A0
int PinY    = A1;   //analog A1
int PinS    = 7;    //digital D7

void setup() {
  //Serial
  Serial.begin(9600);

  Serial.println("PinX setup on pin "+(String)PinX);
  Serial.println("PinY setup on pin "+(String)PinY);
  Serial.println("PinS setup on pin "+(String)PinS);
  
  //Pins
  pinMode(PinX,INPUT);
  pinMode(PinY,INPUT);
  pinMode(PinS,INPUT);

  //instead of using a pullup resistor, write PinS to HIGH to leverage internal pullup resistor (see https://youtu.be/B6YEQj4d5WU?t=784)
  digitalWrite(PinS,HIGH);   
}

void loop() {
  //Read joystick values
  int Xval = analogRead(PinX);
  int Yval = analogRead(PinY);
  bool Sval = digitalRead(PinS);

  //print values
  Serial.println("(X,Y) = (" + (String)Xval + "," + (String)Yval + "), switch = " + (String)Sval);  

  delay(100);
}
