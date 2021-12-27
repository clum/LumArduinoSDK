#ifndef GUARD_LUMHFASTLED_H
#define GUARD_LUMHFASTLED_H

/*
* Version History
* 12/??/21: Created
* 12/26/21: Updated documentation
*/

#include "FastLED.h"

void allOff(CRGB* leds, int numLEDs);
void allOn(CRGB* leds, int numLEDs, CRGB color);
void rise(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms = 20);
void fall(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms = 20);
void riseAndFall(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms = 20);
void rainbowLum(CRGB* leds, int numLEDs);
void rainbowWithGlitterLum(CRGB* leds, int numLEDs, fract8 chanceOfGlitter = 20);
void confettiLum(CRGB* leds, int numLEDs, uint8_t gHue = 200, uint16_t deltaT_ms = 20);
void bpmLum(CRGB* leds, int numLEDs, uint8_t beatsPerMinute = 60, uint8_t gHue = 200);
void sinPulse(CRGB* leds, int numLEDs, CRGB colorA, CRGB colorB, float omega_rps);

void addGlitter(CRGB* leds, int numLEDs, fract8 chanceOfGlitter = 20);

#endif
