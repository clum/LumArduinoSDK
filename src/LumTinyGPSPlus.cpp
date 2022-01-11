#include "LumTinyGPSPlus.h"
#include <Arduino.h>

/// <summary>
/// 
/// </summary>
/// <param name="ms"></param>
void DelayAndEncodeGPSViaSoftwareSerial(unsigned long ms, TinyGPSPlus *gps, SoftwareSerial *ss)
{
    unsigned long start = millis();
    do
    {
        while (ss->available())
            gps->encode(ss->read());
    } while (millis() - start < ms);
}
