/*
Test functions from the LumArrays.h source

Christopher Lum
lum@uw.edu

Version History
12/06/24: Created
12/07/24: Moved to LumArduinoSDK
 */
 
#include <LumArrays.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  int vecI[] = { 2, 3, -5, 1, 23 };
  unsigned int numElementsI = 5;
  int actualI = sum(vecI,numElementsI);
  int averageI = average(vecI,numElementsI);
  
  Serial.println(actualI);
  Serial.println(averageI);
  Serial.println("");
  
  unsigned int numElementsF = 6;
  float vecF[] = { 2.5, 3.2, -5.25, 10.3, -23, 5.234};
  float actualF = sum(vecF,numElementsF);
  float averageF = average(vecF,numElementsF);
  
  Serial.println(actualF);
  Serial.println(averageF);
  Serial.println("");
  
  delay(2000);  
}
