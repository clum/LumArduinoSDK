#include "ArrayManipulation.h"

int sum(int* vec, uint8_t numElements) {
  int sumVec = 0;
  for(int k=0;k<numElements;k++)
  {
    sumVec += vec[k];
  }

  return sumVec;
}

float sum(float* vec, uint8_t numElements) {
  float sumVec = 0;
  for(int k=0;k<numElements;k++)
  {
    sumVec += vec[k];
  }

  return sumVec;
}

int average(int* vec, uint8_t numElements) {
  int sumVec = sum(vec,numElements);
  return sumVec/numElements;
}

float average(float* vec, uint8_t numElements) {
  float sumVec = sum(vec,numElements);
  return sumVec/numElements;
}