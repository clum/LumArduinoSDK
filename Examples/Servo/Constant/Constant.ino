/* 
Move servo to a set/constant position

 On boards other than the Mega, use of the Servo library disables analogWrite() (PWM) functionality on pins 9 and 10, 
 whether or not there is a Servo on those pins (see https://www.arduino.cc/reference/en/libraries/servo/) for more info

Christopher Lum
lum@uw.edu

Version History
11/18/21: Created
11/24/21: Updated documentation
*/

#include <Servo.h>

Servo myservo;
int PinServo = 9;

void setup() {
  myservo.attach(PinServo);
}

void loop() {
  int pos = 90;    //in range of [0,180]
  myservo.write(pos);  
}
