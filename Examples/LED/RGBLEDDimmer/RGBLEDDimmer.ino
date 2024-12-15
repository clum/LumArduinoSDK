/*
Control and external RGB LED and make it dim/fade using analogWrite

Christopher Lum
lum@uw.edu

Version History
10/27/21: created
12/14/24: changed names and pins
*/

//Constants
int PinLED_R = 6;
int PinLED_G = 5;
int PinLED_B = 3;
int delayTime_ms = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PinLED_R, OUTPUT);
  pinMode(PinLED_G, OUTPUT);
  pinMode(PinLED_B, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //Fade red
  for(int brightness = 0; brightness <=255; brightness++) {
    analogWrite(PinLED_R, brightness);
    delay(delayTime_ms);
  }

  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(PinLED_R, brightness);
    delay(delayTime_ms);
  }

  //Fade green
  for(int brightness = 0; brightness <=255; brightness++) {
    analogWrite(PinLED_G, brightness);
    delay(delayTime_ms);
  }

  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(PinLED_G, brightness);
    delay(delayTime_ms);
  }

  //Fade blue
  for(int brightness = 0; brightness <=255; brightness++) {
    analogWrite(PinLED_B, brightness);
    delay(delayTime_ms);
  }

  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(PinLED_B, brightness);
    delay(delayTime_ms);
  }
}
