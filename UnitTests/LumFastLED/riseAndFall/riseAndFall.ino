/*
Test the riseAndFall function from the LumFastLED library.

Christopher Lum
lum@uw.edu

Version History
12/12/21: created
*/

#include <FastLED.h>
#include "LumFastLED.h"

#define LED_TYPE        WS2812
#define LED_COLOR_ORDER GRB

#define PIN_LED         3
#define NUM_LEDS        60

#define BRIGHTNESS      96

//Constants
CRGB leds[NUM_LEDS];

void setup() {
  //Serial
  Serial.begin(9600);
  
  //tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,PIN_LED,LED_COLOR_ORDER>(leds,NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

    //set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  
  CRGB color = CRGB(150,25,10);

  //Chose a pattern
  //rise(leds,NUM_LEDS,color);
  //fall(leds,NUM_LEDS,color);
  riseAndFall(leds,NUM_LEDS,color);
  
  FastLED.show();    
}
