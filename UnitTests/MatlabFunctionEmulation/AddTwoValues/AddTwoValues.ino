/*
Unit test for the MatlabFunctionEmulation\AddTwoValues function.

Christopher Lum
lum@uw.edu

Version History
10/28/21: created
*/

#include <MatlabFunctionEmulation.h>

void setup() {
  //Serial
  Serial.begin(9600);
}

void loop() {
  //use int version of function
  int ai = 3;
  int bi = 5;
  int ci = AddTwoValues(ai,bi);
  
  Serial.println("int version of function");
  Serial.println("ci = " + (String)ci);
  Serial.println("");
  
  //use float version of function
  float af = 3.5;
  float bf = 5.23;
  float cf = AddTwoValues(af,bf);
  
  Serial.println("float version of function");
  Serial.println("cf = " + (String)cf);
  Serial.println(""); 
  
  delay(100);
}
