/*
Control a heater using PWM.  The heater is powered through the IRFZ44N.

Notes:
  -LED should be in series with a current limiting resistor (500 - 1000 ohms).
  -LED should have long leg to pin and short leg closer to ground.
  -Arduino Nano built in LED is on pin D13 (or use LED_BUILTIN)

Christopher Lum
lum@uw.edu

Version History
01/10/25: Created
01/11/25: Adding PWM control
*/

//Constants
int PinPWM = 3;   //pin D3 (has PWM capability)

int stepTime_ms = 15000;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //PWM control
  pinMode(PinPWM,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //Step01
  int dutyCycle = 100;
  analogWrite(PinPWM,dutyCycle);
  Serial.println(dutyCycle);
  delay(stepTime_ms);

  dutyCycle = 200;
  analogWrite(PinPWM,dutyCycle);
  Serial.println(dutyCycle);
  delay(stepTime_ms);

  dutyCycle = 255;
  analogWrite(PinPWM,dutyCycle);
  Serial.println(dutyCycle);
  delay(stepTime_ms);  
}
