/*
Turn on a LED based on the state of a switch via a simple polling technique.

No switches pressed             = green light on
Switch01 pressed                = yellow light on
Switch02 pressed                = red light on
%Switch01 and Switch02 pressed  = yellow and red light on

Christopher Lum
lum@uw.edu

Version History
11/13/21: created
11/14/21: Moved flashing logic to Switch02 example
*/

//Constants
int PinLED_G = A5;
int PinLED_Y = A4;
int PinLED_R = A3;

int PinSwitch01 = 2;
int PinSwitch02 = 3;

int stateSwitch01 = 0;
int stateSwitch02 = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_G,OUTPUT);
  pinMode(PinLED_Y,OUTPUT);
  pinMode(PinLED_R,OUTPUT);

  pinMode(PinSwitch01, INPUT_PULLUP);
  pinMode(PinSwitch02, INPUT_PULLUP);
}

void loop() {
  //determine state of switches
  stateSwitch01 = !digitalRead(PinSwitch01);
  Serial.println("stateSwitch01 = " + (String)stateSwitch01);

  stateSwitch02 = !digitalRead(PinSwitch02);
  Serial.println("stateSwitch02 = " + (String)stateSwitch02);

  if(!stateSwitch01 && !stateSwitch02) {
    //neither switch pressed    
    digitalWrite(PinLED_Y,LOW);
    digitalWrite(PinLED_R,LOW);  

    //execute nominial operations
    digitalWrite(PinLED_G,HIGH);
    
  } else if(stateSwitch01 && !stateSwitch02) {
    //only switch01 pressed
    digitalWrite(PinLED_G,LOW);
    digitalWrite(PinLED_R,LOW);

    //execute switch01 operations
    digitalWrite(PinLED_Y,HIGH);
    
  } else if(!stateSwitch01 && stateSwitch02) {
    //only switch02 pressed
    digitalWrite(PinLED_G,LOW);
    digitalWrite(PinLED_Y,LOW);

    //execute switch02 operations
    digitalWrite(PinLED_R,HIGH);
    
  } else {
    //both switch01 and switch02 pressed
    digitalWrite(PinLED_G,LOW);

    //execute switch01 and switch02 operations
    digitalWrite(PinLED_Y,HIGH);
    digitalWrite(PinLED_R,HIGH);

  }
  
}
