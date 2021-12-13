#ifndef GUARD_LUMHFASTLED_H
#define GUARD_LUMHFASTLED_H

#include "FastLED.h"

void rise(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms = 20);
void fall(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms = 20);
void riseAndFall(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms = 20);
void rainbowLum(CRGB* leds, int numLEDs);
void rainbowWithGlitterLum(CRGB* leds, int numLEDs, fract8 chanceOfGlitter = 20);

void addGlitter(CRGB* leds, int numLEDs, fract8 chanceOfGlitter = 20);

#endif
