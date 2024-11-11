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
int PinCs = 7;      //chip select
int PinClk = 8;     //clock

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinCs,OUTPUT);
  pinMode(PinClk,OUTPUT);

  //setup IC
  digitalWrite(PinCs,HIGH);
  digitalWrite(PinClk,HIGH);
}

// the loop function runs over and over again forever
void loop() {
  /*
  digitalWrite(PinCs,HIGH);
  delay(500);
  digitalWrite(PinCs,LOW);
  delay(100);

  digitalWrite(PinClk,HIGH);
  delay(100);
  digitalWrite(PinClk,LOW);
  delay(100);
  */
  readSensor();
  delay(1000);
}

unsigned int readSensor() {
  unsigned int dataOut = 0;

  digitalWrite(PinCs,LOW);

  //Pulse clock and get bits
  for(int k=0;k<12;k++) {
    digitalWrite(PinClk,LOW);
    delay(100);
    digitalWrite(PinClk,HIGH);
    delay(100);
  }

  //deselect encoder from reading
  digitalWrite(PinCs,HIGH);
  
  return dataOut;
}

unsigned long FrequencyToPeriodMs() {
  //ERROR: START HERE!!!
  return 0;

}