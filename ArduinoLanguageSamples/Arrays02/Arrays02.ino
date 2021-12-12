
/*
Passing arrays to functions.

Christopher Lum
lum@uw.edu

Version History
12/10/21: created
12/11/21: changed dependencies to LumCSDK
*/

//#include <Arduino.h>
//#include "ArrayManipulation.h"
#include "LumArrays.h"

void setup() {
  //Serial
  Serial.begin(9600);  
}

void loop() {
  int vec_int[] = {2, 2, 3, 4, 5};
  float vec_float[] = {2, 2, 3, 4, 5};
  
  uint8_t numElements = 5;

  //compute the average
  int sum_int = sum(vec_int,numElements);
  float sum_float = sum(vec_float,numElements);
  
  int ave_int = average(vec_int,numElements);
  float ave_float = average(vec_float,numElements);
  
  Serial.println("sum_int = "+(String)sum_int);
  Serial.println("ave_int = "+(String)ave_int);
  Serial.println("");
  
  Serial.println("sum_float = "+(String)sum_float);
  Serial.println("ave_float = "+(String)ave_float);
  Serial.println("");

  delay(3000);
}
