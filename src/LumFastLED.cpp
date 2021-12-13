#include "LumFastLED.h"
#include "FastLED.h"

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

    //how much time has elapsed since we last lit and LED?
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

    //how much time has elapsed since we last lit and LED?
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

    //how much time has elapsed since we last lit and LED?
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