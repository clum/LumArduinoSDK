/*
Use a switch with an internal pullup resistor.

Christopher Lum
lum@uw.edu

Version History
12/18/21: created
*/

//Constants
int PinSwitch = 2;

int stateSwitch = 0;

void setup() {
  //Serial
  Serial.begin(9600);
  
  pinMode(PinSwitch, INPUT_PULLUP);
}

void loop() {
  //determine state of switches
  stateSwitch = !digitalRead(PinSwitch);
  Serial.println(stateSwitch);
}
  
