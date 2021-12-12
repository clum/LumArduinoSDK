/*
Similar to Switch01 except this flashes the LED which takes a finite amount of time to illustrate that 
polling cannot interrupt behavior.

No switches pressed             = green light flashing
Switch01 pressed                = yellow light flashing
Switch02 pressed                = red light flashing
%Switch01 and Switch02 pressed  = yellow and red light flashing

Christopher Lum
lum@uw.edu

Version History
11/13/21: created
11/14/21: changed name
*/

//Constants
int PinLED_G = A5;
int PinLED_Y = A4;
int PinLED_R = A3;

int PinSwitch01 = 2;
int PinSwitch02 = 3;

int stateSwitch01 = 0;
int stateSwitch02 = 0;

int blinkTime01_ms = 1000;
int blinkTime02_ms = 500;
int blinkTime03_ms = 200;

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
    delay(blinkTime01_ms);
    digitalWrite(PinLED_G,LOW);
    delay(blinkTime01_ms);

    digitalWrite(PinLED_G,HIGH);
    delay(blinkTime02_ms);
    digitalWrite(PinLED_G,LOW);
    delay(blinkTime02_ms);

    digitalWrite(PinLED_G,HIGH);
    delay(blinkTime03_ms);
    digitalWrite(PinLED_G,LOW);
    delay(blinkTime03_ms);
    
  } else if(stateSwitch01 && !stateSwitch02) {
    //only switch01 pressed
    digitalWrite(PinLED_G,LOW);
    digitalWrite(PinLED_R,LOW);

    //execute switch01 operations
    digitalWrite(PinLED_Y,HIGH);
    delay(blinkTime01_ms);
    digitalWrite(PinLED_Y,LOW);
    delay(blinkTime01_ms);

    digitalWrite(PinLED_Y,HIGH);
    delay(blinkTime02_ms);
    digitalWrite(PinLED_Y,LOW);
    delay(blinkTime02_ms); 

    digitalWrite(PinLED_Y,HIGH);
    delay(blinkTime03_ms);
    digitalWrite(PinLED_Y,LOW);
    delay(blinkTime03_ms); 
    
  } else if(!stateSwitch01 && stateSwitch02) {
    //only switch02 pressed
    digitalWrite(PinLED_G,LOW);
    digitalWrite(PinLED_Y,LOW);

    //execute switch02 operations
    digitalWrite(PinLED_R,HIGH);
    delay(blinkTime01_ms);
    digitalWrite(PinLED_R,LOW);
    delay(blinkTime01_ms);
    digitalWrite(PinLED_R,HIGH);
    delay(blinkTime02_ms);
    digitalWrite(PinLED_R,LOW);
    delay(blinkTime02_ms);
    digitalWrite(PinLED_R,HIGH);
    delay(blinkTime03_ms);
    digitalWrite(PinLED_R,LOW);
    delay(blinkTime03_ms);
    
  } else {
    //both switch01 and switch02 pressed
    digitalWrite(PinLED_G,LOW);

    //execute switch01 and switch02 operations
    digitalWrite(PinLED_Y,HIGH);
    digitalWrite(PinLED_R,HIGH);
    delay(blinkTime01_ms);
    digitalWrite(PinLED_Y,LOW);
    digitalWrite(PinLED_R,LOW);
    delay(blinkTime01_ms);

    digitalWrite(PinLED_Y,HIGH);
    digitalWrite(PinLED_R,HIGH);
    delay(blinkTime02_ms);
    digitalWrite(PinLED_Y,LOW);
    digitalWrite(PinLED_R,LOW);
    delay(blinkTime02_ms);

    digitalWrite(PinLED_Y,HIGH);
    digitalWrite(PinLED_R,HIGH);
    delay(blinkTime03_ms);
    digitalWrite(PinLED_Y,LOW);
    digitalWrite(PinLED_R,LOW);
    delay(blinkTime03_ms);
  }
  
}
