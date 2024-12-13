//This code was obtained from https://github.com/SuperDroidRobots/Encoder-Buffer-Breakout/blob/master/DualEncoderBreakout/DualEncoderBreakout.ino

//=========================HEADER=============================================================
/*
   Single LS7366 Quadrature Counter Test Code
   
   This is a simple test program to read encoder counts
   collected by the LS7366 breakout board. The counts are
   then displayed in the Arduino's serial monitor at a 
   baud rate of 9600

   This was tested with an Arduino Due.

   1.  Make hardware connections (see below).
   2.  Upload this code to Arduino
   3.  Ensure function generator or crystal oscillator is generating an input to fCKi
   4.  Start Arduino IDE serial monitor to see output (Tools > Serial Monitor)
   5.  Spin the motor, you should see output on the serial monitor.
      
   LS7366 Breakout    -------------   Arduino
   -----------------                    -------
            MOSI   -------------------   SDO (SPI header)
            MISO   -------------------   SDI (SPI header)
            SCK    -------------------   SCK (SPI header)
            SS     -------------------   SS (see slaveSelectEncPin variable)
            GND    -------------------   GND
            VDD    -------------------   VCC (3.3V)
            fCKi   -------------------   Function generator with [0,5] square wave at high frequency (

   License: CCAv3.0 Attribution-ShareAlike (http://creativecommons.org/licenses/by-sa/3.0/)
   You're free to use this code for any venture. Attribution is greatly appreciated. 
   
  AUTHOR: Jason Traud   
  DATE: June 22, 2013

  Modified by Christopher Lum
  Version History:
  12/11/16: Modified from original code (dual encoders) to a single encoder
  12/12/16: Added debugging functions
  12/14/16: Updated and verified to work.
  12/28/16: Continued working
  01/26/17: Tested with fCKi driven by a function generator from [0,5] volts at 30 kHz.  Verified to work.
  01/03/18: Verified to work with fCKi driven by on board C01100 oscillator (no longer needs an external function generator)
  03/14/18: Updated documentation

//============================================================================================
*/

// Include the standard Arduino SPI Library, please ensure the SPI pins are
// connected properly for your Arduino version
#include <SPI.h>

//how many bytes do we want to set the counter mode to (1, 2, 3, or 4)
const int numBytesCounterMode = 4;  

// Slave Select pins for encoders
// Feel free to reallocate these pins to best suit your circuit
const int slaveSelectEncPin = 52;

// These hold the current encoder count.
signed long encoderCount = 0;


/*
 * Initialize the LS7366
 */
void initEncoder() {
  
  // Set slave selects as outputs
  pinMode(slaveSelectEncPin, OUTPUT);
  
  // Raise select pins
  // Communication begins when you drop the individual select signsl
  digitalWrite(slaveSelectEncPin,HIGH);
  
  SPI.begin();

  //Write MDR0
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation (AKA new command)
  SPI.transfer(0x88);                       // Write to MDR0
  SPI.transfer(0x03);                       // clock division factor = 1, negative index input, disable index, free-running count mode, 4x quadrature count mode
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations

  //Write MDR1
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation (AKA new command)
  SPI.transfer(0x90);                       // Write to MDR1

  if(numBytesCounterMode==1)
  {
    SPI.transfer(0x03);                       //no flags, enable counting, 1-byte counter mode
  }
  else if(numBytesCounterMode==4)
  {
    SPI.transfer(0x00);                       //no flags, enable counting, 4-byte counter mode
  }
  else
  {
    Serial.println("ERROR: Unsupported value of numBytesCounterMode");
    exit(0);
  }
  
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation

  delayMicroseconds(100);  // provides some breathing room between SPI conversations

  //Clear STR
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation (AKA new command)
  SPI.transfer(0x30);                       // Clear STR
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation

  delayMicroseconds(100);  // provides some breathing room between SPI conversations

  //Clear CNTR
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation (AKA new command)
  SPI.transfer(0x20);                       // Clear CNTR
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation

  delayMicroseconds(100);  // provides some breathing room between SPI conversations
}

/*
 * Read the CNTR register (encoder counts) and return the count.
 */
long readEncoder() {  
  // Initialize temporary variables for SPI read
  unsigned int count_1, count_2, count_3, count_4;
  long count_value;  
  
  digitalWrite(slaveSelectEncPin,LOW);    // Begin SPI conversation
  SPI.transfer(0x60);                     // Read from CNTR

  //read appropriate number of bytes
  if(numBytesCounterMode==1)
  {
    count_1 = SPI.transfer(0x00);           // Read highest order byte
  }
  else if(numBytesCounterMode==4)
  {  
    count_1 = SPI.transfer(0x00);           // Read highest order byte
    count_2 = SPI.transfer(0x00);           
    count_3 = SPI.transfer(0x00);           
    count_4 = SPI.transfer(0x00);           // Read lowest order byte
  }
  else
  {
    Serial.println("ERROR: Unsupported value of numBytesCounterMode");
    exit(0);
  }

  digitalWrite(slaveSelectEncPin,HIGH);   // Terminate SPI conversation 
  
  // Calculate encoder count
  if(numBytesCounterMode==1)
  {
    count_value = count_1;
  }
  else if(numBytesCounterMode==4)
  {  
    count_value = (count_1 << 8) + count_2;
    count_value = (count_value << 8) + count_3;
    count_value = (count_value << 8) + count_4;
  }
  else
  {
    Serial.println("ERROR: Unsupported value of numBytesCounterMode");
    exit(0);
  }
  
  return count_value;
}

/*
 * Set the encoder count to zero
 */
void clearEncoderCount() {    
  // Set DTR to 0
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation  
  SPI.transfer(0x98);        // Write to DTR
  if(numBytesCounterMode==1)
  {
    SPI.transfer(0x00);        // Highest order byte
  }
  else if(numBytesCounterMode==4)
  {  
    SPI.transfer(0x00);        // Highest order byte
    SPI.transfer(0x00);           
    SPI.transfer(0x00);           
    SPI.transfer(0x00);        // lowest order byte
  }
  else
  {
    Serial.println("ERROR: Unsupported value of numBytesCounterMode");
    exit(0);
  }

  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
  
  // transfer DTR to CNTR
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation  
  SPI.transfer(0xE0);    
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation   
}

/*
 * Read and display the MDR0 register value
 */
void readMDR0()
{
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation  
  SPI.transfer(0x48);        // Read MDR0
  int value = SPI.transfer(0x00);           
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
    
  Serial.print("MDR0 (Hex): ");
  Serial.println(value, HEX);
}

/*
 * Read and display the MDR1 register value
 */
void readMDR1()
{
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation  
  SPI.transfer(0x50);        // Read MDR1
  int value = SPI.transfer(0x00);   
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
    
  Serial.print("MDR1 (Hex): ");
  Serial.println(value, HEX);
}

/*
 * Read and display the STR register value
 */
void readSTR()
{
  digitalWrite(slaveSelectEncPin,LOW);      // Begin SPI conversation  
  SPI.transfer(0x70);        // Read STR
  int value = SPI.transfer(0x00);   
  digitalWrite(slaveSelectEncPin,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
    
  Serial.print("STR (binary): ");
  Serial.println(value, BIN);
}

/////////////////////////////////////////////////////////////////////////////////
void setup() {
 Serial.begin(9600);      // Serial com for data output
 
 initEncoder();       
 Serial.println("Encoders Initialized...");  
 
 clearEncoderCount();  
 Serial.println("Encoders Cleared...");
}

void loop() {
  //display diagnostic information
  readMDR0();
  readMDR1();
  readSTR();

  //read the encoder counts
  encoderCount = readEncoder();
  Serial.print("encoderCount (decimal): ");
  Serial.println(encoderCount);
  Serial.println("");
  delay(500);
}
