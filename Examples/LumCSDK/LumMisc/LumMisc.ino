/*
Test functions from the LumMisc.h source

Christopher Lum
lum@uw.edu

Version History
12/06/24: Created
12/07/24: Moved to LumArduinoSDK
 */
 
#include <LumMisc.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  uint8_t x = 0b10101010;
  char position = 6;

  uint8_t y = BitSetTo1(x,position);
  uint8_t z = BitFlip(y,position);
  
  Serial.print("BitIs1: ");
  Serial.println(BitIs1(x,position));

  Serial.print("BitSetTo1: ");
  Serial.println(y);

  Serial.print("BitFlip: ");
  Serial.println(z);
  
  Serial.println("");
  
  delay(2000);
  
}
