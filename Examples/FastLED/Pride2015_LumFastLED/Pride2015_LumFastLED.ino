#include "FastLED.h"
#include "LumFastLED.h"

/*
Modify the Pride2015 example by Mark Kriegsman from the FastLED library for other purposes.

This moves functionality to the Rainbow function

Modified by Christopher Lum
lum@uw.edu

Version History
12/12/21: Created
 */


#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define PIN_LED     3
#define NUM_LEDS    60

#define BRIGHTNESS  10

//constants
CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,PIN_LED,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
  rainbow(leds,NUM_LEDS);
  FastLED.show();  
}
