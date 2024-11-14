/*
Script to interface with the AET-6600-T16 encoder.

Notes:
  -Each LED should be in series with a current limiting resistor (500 - 1000 ohms).
  -LED should have long leg to pin and short leg closer to ground.
  -Arduino Nano built in LED is on pin D13 (or use LED_BUILTIN)

Christopher Lum
lum@uw.edu

Version History
11/13/24: Created
*/

//Constants
int PinCs     = 7;  //chip select
int PinClk    = 8;  //clock
int PinMagHi  = 2;  //magnet hi input
int PinMagLo  = 4;  //magnet lo input

const int DATA_PIN = 6;
const int BIT_COUNT = 10; // quasi works
//const int BIT_COUNT = 12; // quasi works
//const int BIT_COUNT = 14; // quasi works
//const int BIT_COUNT = 16; // quasi works


//TEMP
int PinMagHiEmulate = 9;  //magnet hi output
int PinMagLoEmulate = 10; //magnet lo output

// the setup function runs once when you press reset or power the board
void setup() {
  //Serial
  Serial.begin(9600);
  
  pinMode(PinCs,OUTPUT);
  pinMode(PinClk,OUTPUT);

  pinMode(PinMagHi,INPUT);
  pinMode(PinMagLo,INPUT);

  pinMode(DATA_PIN, INPUT);

  pinMode(PinMagHiEmulate,OUTPUT);
  pinMode(PinMagLoEmulate,OUTPUT);

  //setup IC
  digitalWrite(PinCs,HIGH);
  digitalWrite(PinClk,HIGH);

  digitalWrite(PinMagHiEmulate,LOW);
  digitalWrite(PinMagLoEmulate,LOW);
}

// the loop function runs over and over again forever
void loop() {

  /*
  //emulate the magnet moving in and out
  digitalWrite(PinMagHiEmulate,HIGH);
  digitalWrite(PinMagLoEmulate,LOW);
  readMagState();
  delay(500);

  digitalWrite(PinMagHiEmulate,HIGH);
  digitalWrite(PinMagLoEmulate,HIGH);
  readMagState();
  delay(500);
  
  digitalWrite(PinMagHiEmulate,LOW);
  digitalWrite(PinMagLoEmulate,HIGH);
  readMagState();
  delay(500);
  
  digitalWrite(PinMagHiEmulate,LOW);
  digitalWrite(PinMagLoEmulate,LOW);
  readMagState();
  delay(500);    
  */

  /*
  readMagState();
  delay(50);
  */

/*
  //generate clock pulses
  readSensor();
  */

/*
  float reading = readPosition();
  if (reading >= -0.5)
  {
    Serial.print("Reading: ");
    Serial.println(reading, 2);
  }
*/


  unsigned long reading = readPositionInt();
    Serial.print("Reading: ");
    Serial.println(reading);
  
  delay(50);
}

/*
Read the state of the magnet and print to serial for debugging
 */
void readMagState() {
  int magHi = digitalRead(PinMagHi);
  int magLo = digitalRead(PinMagLo);

  Serial.println(magHi);
  Serial.println(magLo);
  Serial.println(millis());
}

unsigned int readSensor() {
  unsigned int dataOut = 0;

  digitalWrite(PinCs,LOW);

  //Pulse clock and get bits
  for(int k=0;k<12;k++) {
    digitalWrite(PinClk,LOW);
    delayMicroseconds(2); 
    digitalWrite(PinClk,HIGH);
    delayMicroseconds(2);     
  }

  //deselect encoder from reading
  digitalWrite(PinCs,HIGH);
  
  return dataOut;
}



//read the current angular position
float readPosition()
{
  // Read the same position data twice to check for errors
  unsigned long sample1 = shiftIn(DATA_PIN, PinClk, PinCs, BIT_COUNT);
  unsigned long sample2 = shiftIn(DATA_PIN, PinClk, PinCs, BIT_COUNT);
  delayMicroseconds(20); // Clock must be high for 20 microseconds before a new sample can be taken
  if (sample1 != sample2) return -1.0;
  return ((sample1 & 0x0FFF) * 360UL) / 4096.0;
}

//read the current angular position
unsigned long readPositionInt()
{
  // Read the same position data twice to check for errors
  unsigned long sample1 = shiftIn(DATA_PIN, PinClk, PinCs, BIT_COUNT);
  unsigned long sample2 = shiftIn(DATA_PIN, PinClk, PinCs, BIT_COUNT);
  delayMicroseconds(20); // Clock must be high for 20 microseconds before a new sample can be taken
  if (sample1 != sample2) return 0UL;
  return sample1;
}

//read in a byte of data from the digital input of the board.
unsigned long shiftIn(const int data_pin, const int clock_pin, const int cs_pin, const int bit_count)
{
  unsigned long data = 0;

  digitalWrite(cs_pin, LOW);
  for (int i = 0; i < bit_count; i++)
  {
    data <<= 1;
    digitalWrite(clock_pin, LOW);
    delayMicroseconds(1);
    digitalWrite(clock_pin, HIGH);
    delayMicroseconds(1);

    data |= digitalRead(data_pin);
  }
  digitalWrite(cs_pin, HIGH);
  return data;
}


/*

 */
unsigned long FrequencyToPeriodMs(unsigned int fHz) {
  //ERROR: START HERE!!!
  return 0;

}
