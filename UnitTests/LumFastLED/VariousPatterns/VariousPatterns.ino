/*
Test the various pattern generator functions from the LumFastLED library.

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

#define BRIGHTNESS      30

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
  //user selections
  int patternSelection = 6;
  
  //Chose a pattern
  if(patternSelection==0) {
    CRGB color = CRGB(150,25,10);
    uint16_t deltaT_ms = 100;
    rise(leds,NUM_LEDS,color,deltaT_ms);
    
  } 
  else if(patternSelection==1) {
    CRGB color = CRGB(25,150,10);
    uint16_t deltaT_ms = 50;    
    fall(leds,NUM_LEDS,color,deltaT_ms);
    
  }
  else if(patternSelection==2) {
    CRGB color = CRGB(25,10,150);
    uint16_t deltaT_ms = 20;        
    riseAndFall(leds,NUM_LEDS,color,deltaT_ms);
    
  }
  else if(patternSelection==3) {
    rainbowLum(leds,NUM_LEDS);
    
  }
  else if(patternSelection==4) {
    fract8 chanceOfGlitter = 20;
    rainbowWithGlitterLum(leds, NUM_LEDS, chanceOfGlitter);
    
  }
  else if(patternSelection==5) {
    uint8_t gHue = 200; //"base color"
    uint16_t deltaT_ms = 20;    
    confettiLum(leds,NUM_LEDS,gHue,deltaT_ms);
    
  }
  else if(patternSelection==6) {
    uint8_t beatsPerMinute = 60;
    uint8_t gHue = 75; //"base color"
    bpmLum(leds,NUM_LEDS,beatsPerMinute,gHue);
    
  }
  else {
    allOff(leds,NUM_LEDS);
    
  }

  //display LED sequence
  FastLED.show();    
}
