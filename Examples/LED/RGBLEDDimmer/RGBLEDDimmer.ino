/*
Control and external RGB LED and make it dim/fade using analogWrite

Christopher Lum
lum@uw.edu

Version History
10/27/21: created
*/

//Constants
int PinLEDRed   = 2;
int PinLEDGreen = 3;
int PinLEDBlue  = 4;
int delayTime_ms = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PinLEDRed, OUTPUT);
  pinMode(PinLEDGreen, OUTPUT);
  pinMode(PinLEDBlue, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //Fade red
  for(int brightness = 0; brightness <=255; brightness++) {
    analogWrite(PinLEDRed, brightness);
    delay(delayTime_ms);
  }

  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(PinLEDRed, brightness);
    delay(delayTime_ms);
  }

  //Fade green
  for(int brightness = 0; brightness <=255; brightness++) {
    analogWrite(PinLEDGreen, brightness);
    delay(delayTime_ms);
  }

  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(PinLEDGreen, brightness);
    delay(delayTime_ms);
  }

  //Fade blue
  for(int brightness = 0; brightness <=255; brightness++) {
    analogWrite(PinLEDBlue, brightness);
    delay(delayTime_ms);
  }

  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(PinLEDBlue, brightness);
    delay(delayTime_ms);
  }
}
