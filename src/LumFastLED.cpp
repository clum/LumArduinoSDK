#include "LumFastLED.h"
#include "FastLED.h"

/// <summary>
/// Turn off all LEDs
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
void allOff(CRGB* leds, int numLEDs)
{
    //turn off all LEDs
    for (int k = 0; k < numLEDs; k++) {
        leds[k] = CRGB(0, 0, 0);        
    }
}

/// <summary>
/// Generate LED pattern of a rising bar.
/// 
/// Example usage:
///     
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="color"></param>
/// <param name="deltaT_ms">optional: time between subsequent LEDs (ms)</param>
void rise(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms)
{
    static uint16_t sLastMillis = 0;
    static unsigned int numLit = 0;

    //how much time has elapsed since we last lit an LED?
    uint16_t ms = millis();
    uint16_t delta_ms = ms - sLastMillis;

    //is it time to light another LED?
    if (delta_ms > deltaT_ms) {
        if (numLit == numLEDs - 1) {
            numLit = 0;
        } 
        else {
            numLit += 1;
        }

        sLastMillis = ms;
    }

    //light appropriate number of LEDs
    for (int k = 0; k < numLEDs; k++) {
        if (k <= numLit) {
            leds[k] = color;
        } 
        else {
            leds[k] = CRGB(0, 0, 0);
        }
    }
}

/// <summary>
/// Generate LED pattern of a falling bar.
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="color"></param>
/// <param name="deltaT_ms">optional: time between subsequent LEDs (ms)</param>
void fall(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms)
{
    static uint16_t sLastMillis = 0;
    static unsigned int numLit = 0;

    //how much time has elapsed since we last lit an LED?
    uint16_t ms = millis();
    uint16_t delta_ms = ms - sLastMillis;

    //is it time to unlight another LED?
    if (delta_ms > deltaT_ms) {
        if (numLit == 0) {
            numLit = numLEDs - 1;
        } 
        else {
            numLit -= 1;
        }

        sLastMillis = ms;
    }

    //light appropriate number of LEDs
    for (int k = 0; k < numLEDs; k++) {
        if (k <= numLit) {
            leds[k] = color;
        } 
        else {
            leds[k] = CRGB(0, 0, 0);
        }
    }
}

/// <summary>
/// Generate LED pattern of a rising then falling bar.
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="color"></param>
/// <param name="deltaT_ms">optional: time between subsequent LEDs (ms)</param>
void riseAndFall(CRGB* leds, int numLEDs, CRGB color, uint16_t deltaT_ms)
{
    static uint16_t sLastMillis = 0;
    static unsigned int numLit = 0;
    static bool directionRise = 1;

    //how much time has elapsed since we last lit an LED?
    uint16_t ms = millis();
    uint16_t delta_ms = ms - sLastMillis;

    //is it time to change LED status?
    if (delta_ms > deltaT_ms) {
        if (directionRise) {
            //rising
            if (numLit == numLEDs - 1) {
                directionRise = 0;
            }
            else {
                numLit += 1;
            }

        }
        else {
            //falling
            if (numLit == 0) {
                directionRise = 1;
            }
            else {
                numLit -= 1;
            }

        }

        sLastMillis = ms;
    }

    //light appropriate number of LEDs
    for (int k = 0; k < numLEDs; k++) {
        if (k <= numLit) {
            leds[k] = color;
        }
        else {
            leds[k] = CRGB(0, 0, 0);
        }
    }

}

/// <summary>
/// Modify the Pride2015 example by Mark Kriegsman from the FastLED library to isolate the rainbow generating code to a function.
/// This function draws rainbows with an ever-changing widely-varying set of parameters.
/// </summary>
/// <param name="leds">point to an array of CRGB objects</param>
/// <param name="numLEDs">number of LEDs</param>
/// <returns></returns>
void rainbowLum(CRGB* leds, int numLEDs)
{
    static uint16_t sPseudotime = 0;
    static uint16_t sLastMillis = 0;
    static uint16_t sHue16 = 0;

    uint8_t sat8 = beatsin88(87, 220, 250);
    uint8_t brightdepth = beatsin88(341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 1, 3000);

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis;
    sLastMillis = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88(400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for (uint16_t i = 0; i < numLEDs; i++) {
        hue16 += hueinc16;
        uint8_t hue8 = hue16 / 256;

        brightnesstheta16 += brightnessthetainc16;
        uint16_t b16 = sin16(brightnesstheta16) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        CRGB newcolor = CHSV(hue8, sat8, bri8);

        uint16_t pixelnumber = i;
        pixelnumber = (numLEDs - 1) - pixelnumber;

        nblend(leds[pixelnumber], newcolor, 64);
    }
}

/// <summary>
/// Similar to rainbowLum but add sparkling glitter effects
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="chanceOfGlitter">See addGlitter</param>
void rainbowWithGlitterLum(CRGB* leds, int numLEDs, fract8 chanceOfGlitter)
{
    rainbowLum(leds, numLEDs);
    addGlitter(leds, numLEDs, chanceOfGlitter);
}

/// <summary>
/// random colored speckles that blink in and fade smoothly
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="gHue"></param>
/// <param name="deltaT_ms"></param>
void confettiLum(CRGB* leds, int numLEDs, uint8_t gHue, uint16_t deltaT_ms)
{
    //function options
    uint8_t fadeBy = 10;

    //static variables
    static uint16_t sLastMillis = 0;

    //how much time has elapsed since we last updated an LED?
    uint16_t ms = millis();
    uint16_t delta_ms = ms - sLastMillis;

    //is it time to light another LED?
    if (delta_ms > deltaT_ms) {
        /*
        From colorutils.h
        // fadeToBlackBy and fade_raw - reduce the brightness of an array
        //                              of pixels all at once.  These
        //                              functions will eventually fade all
        //                              the way to black.
        //                              (The two names are synonyms.)
        void fadeToBlackBy( CRGB* leds, uint16_t num_leds, uint8_t fadeBy);
         */
        fadeToBlackBy(leds, numLEDs, fadeBy);
        int pos = random16(numLEDs);
        leds[pos] += CHSV(gHue + random8(64), 200, 255);

        sLastMillis = ms;
    }
}

/// <summary>
/// Colored stripes pulsing at a defined Beats-Per-Minute (BPM)
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="beatsPerMinute"></param>
/// <param name="gHue"></param>
void bpmLum(CRGB* leds, int numLEDs, uint8_t beatsPerMinute, uint8_t gHue)
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(beatsPerMinute, 64, 255);
    for (int i = 0; i < numLEDs; i++) {
        leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

/// <summary>
/// Adds a sparkling/glitter effect to a pattern by randomly turning some LEDs on to full white.
/// </summary>
/// <param name="leds"></param>
/// <param name="numLEDs"></param>
/// <param name="chanceOfGlitter">value between 0 and 100 (default value of 20)</param>
void addGlitter(CRGB* leds, int numLEDs, fract8 chanceOfGlitter)
{
    if (random8() < chanceOfGlitter) {
        leds[random16(numLEDs)] += CRGB::White;
    }
}