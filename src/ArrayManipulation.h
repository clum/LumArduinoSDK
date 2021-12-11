#ifndef GUARD_ARRAYMANIPULATION_H
#define GUARD_ARRAYMANIPULATION_H

#include <Arduino.h>

int sum(int* vec, uint8_t numElements);
float sum(float* vec, uint8_t numElements);

int average(int* vec, uint8_t numElements);
float average(float* vec, uint8_t numElements);
	
#endif
