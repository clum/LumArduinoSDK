/*
Simple example to show how to interface with the micro SD card adapter.

This writes (appends to a file).

See https://learn.adafruit.com/adafruit-micro-sd-breakout-board-card-tutorial/introduction for more information.

Christopher Lum
lum@uw.edu

Version History
12/26/21: created
12/27/21: Adding writing during the loop portion
*/

#include <SD.h>
 
File myFile;
 
void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
 
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing (appending) to test.txt...");
    myFile.println("testing 1, 2, 3.");
    
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop()
{
  myFile = SD.open("test.txt", FILE_WRITE);

  uint16_t t_ms = millis();
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Inside loop: writing to test.txt.  t_ms = "+(String)t_ms);
    
    myFile.println((String)t_ms);
    
    // close the file:
    myFile.close();
    Serial.println("closed file.");
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  delay(500);
}
