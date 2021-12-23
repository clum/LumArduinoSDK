/*
Detect when a rising edge is triggered.

Christopher Lum
lum@uw.edu

Version History
12/18/21: created
*/

//Constants
int PinSwitch = 2;

int lastSwitchState = 0;

void setup() {
  //Serial
  Serial.begin(9600);
  
  pinMode(PinSwitch, INPUT_PULLUP);
}

void loop() {
  //determine state of switch
  int stateSwitch = !digitalRead(PinSwitch);
  
  //detect rising edge
  int risingEdge = 0;
  if(stateSwitch != lastSwitchState) {
    //change in state
    if(stateSwitch==1) {
      //switch went high
      risingEdge = 1;
    } else {
      //switch went low
      risingEdge = 0;
    }

    lastSwitchState = stateSwitch;
    
  } else {
    //state is the same
    risingEdge = 0;
  }

  //print results
  Serial.println((String)stateSwitch + "," + (String)risingEdge);
}
  
