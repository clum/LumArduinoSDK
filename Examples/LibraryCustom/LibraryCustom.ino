/*
Illustrate how to call/use a custom library.

Christopher Lum
lum@uw.edu

Version History
10/28/21: Created
*/

#include <LumLibrary.h>
#include <LumLibrary2.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  int a = 2;
  int b = 5;
  int c = addTwoInts(a,b);
  int d = subtractTwoInts(a,b);
  
  Serial.println("calling function 1: " + (String)c);
  Serial.println("calling function 2: " + (String)d);
  Serial.println("");

  delay(100);
}
