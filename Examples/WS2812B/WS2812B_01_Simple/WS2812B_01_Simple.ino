/*
Simple example to show how to interface with the WS2812B individually addressable LED strip.

See https://www.youtube.com/watch?v=UhYu0k2woRM for more information.

Christopher Lum
lum@uw.edu

Version History
12/12/21: created
*/

#include <FastLED.h>
#define LED_TYPE        WS2812
#define LED_COLOR_ORDER GRB

#define PIN_LED         7
#define NUM_LEDS        60

//Constants
CRGB leds[NUM_LEDS];

void setup() {
  //Serial
  Serial.begin(9600);
  
  //WS2912B
  FastLED.addLeds<LED_TYPE,PIN_LED,LED_COLOR_ORDER>(leds,NUM_LEDS);
}

void loop() {
    int brightness = 10;
    int delay_ms = 20;

    //increasing in red
    for(int k=0;k<NUM_LEDS;k++) {
      leds[k] = CRGB(brightness,0,0);
      FastLED.show();
      delay(delay_ms);  
    }

    //decreasing in green
    for(int k=NUM_LEDS-1;k>=0;k--) {
      leds[k] = CRGB(0,brightness,0);
      FastLED.show();
      delay(delay_ms);  
    }

    //increasing in blue
    for(int k=0;k<NUM_LEDS;k++) {
      leds[k] = CRGB(0,0,brightness);
      FastLED.show();
      delay(delay_ms);  
    }

    //decreasing in mixed color
    for(int k=NUM_LEDS-1;k>=0;k--) {
      leds[k] = CRGB(brightness,brightness,0);
      FastLED.show();
      delay(delay_ms);  
    }
   
}
