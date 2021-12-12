/*
Turn on a LED based on the state of a switch.  This uses interrupts.

Christopher Lum
lum@uw.edu

Version History
11/13/21: created
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

//interrupt variables
int numTimesISR01Called = 0;
int numTimesISR02Called = 0;

int debounceTime_ms = 100;
unsigned long lastSwitch01PressedTime_ms = 0;
unsigned long lastSwitch02PressedTime_ms = 0;

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

  //Interrupts
  attachInterrupt(digitalPinToInterrupt(PinSwitch01),switch01Pressed,FALLING);
  attachInterrupt(digitalPinToInterrupt(PinSwitch02),switch02Pressed,FALLING);
}

void loop() {
  //determine state of switches (done by interrupts)
  
  //Execute finite state machine
  if(!stateSwitch01 && !stateSwitch02) {
    //neither switch pressed
    Serial.println("neither switch pressed");
    
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

    //reset state of switches
    stateSwitch01 = false;
    stateSwitch02 = false;
    
  } else if(stateSwitch01 && !stateSwitch02) {
    //only switch01 pressed
    Serial.println("switch01 pressed");
    
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

    //reset state of switches
    stateSwitch01 = false;
    stateSwitch02 = false;
    
  } else if(!stateSwitch01 && stateSwitch02) {
    //only switch02 pressed
    Serial.println("switch02 pressed");
    
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

    //reset state of switches
    stateSwitch01 = false;
    stateSwitch02 = false;
    
  } else {
    //both switch01 and switch02 pressed
    Serial.println("switch01 and switch02 pressed");
    
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

    //reset state of switches
    stateSwitch01 = false;
    stateSwitch02 = false;
  }
}

//--------------------------
//Interrupt Service Routines
//--------------------------
void switch01Pressed() {
  unsigned long switch01PressedTime_ms = millis();

  if(switch01PressedTime_ms - lastSwitch01PressedTime_ms >= debounceTime_ms) {
    //valid switch press
    numTimesISR01Called++;
    stateSwitch01 = true;
    Serial.println("   numTimesISR01Called = " + (String)numTimesISR01Called);
    Serial.println("   stateSwitch01 = " + (String)stateSwitch01);  
    lastSwitch01PressedTime_ms = switch01PressedTime_ms;

  } else {
    //debouncing
    Serial.println("   switch01 debouncing");
  }
}

void switch02Pressed() {
  unsigned long switch02PressedTime_ms = millis();

  if(switch02PressedTime_ms - lastSwitch02PressedTime_ms >= debounceTime_ms) {
    //valid switch press
    numTimesISR02Called++;    
    stateSwitch02 = true;
    Serial.println("   numTimesISR02Called = " + (String)numTimesISR02Called);
    Serial.println("   stateSwitch02 = " + (String)stateSwitch02);  
    lastSwitch02PressedTime_ms = switch02PressedTime_ms;

  } else {
    //debouncing
    Serial.println("   switch02 debouncing");
  }
}
